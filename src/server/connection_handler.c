/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my.h"

void logout_handler(server **serv, client *current_client, int sd)
{
    char *file = malloc(sizeof(char) * 1024);
    strcpy(file, "data/users/");
    if (args_check((*serv)->command, 1, sd) == false)
        return;
    if (user_not_connected(current_client) == true)
        return;
    void *function =
    load_library_function((*serv)->lib, "server_event_user_logged_out");
    ((void (*)(char *))function)(current_client->uuid_text);
    send(sd, "200 Logout ok.\n", 15, 0);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    replace_line_file("##STATUS 1", "##STATUS 0",
    strcat(file, current_client->uuid_text));
    remove_client(current_client, sd);
}

void parse_user_data_login(char **usr, client *current_client)
{
    char *file = malloc(sizeof(char) * 1024);
    strcpy(file, "data/users/");
    for (int i = 0; usr[i] != NULL; i++) {
        char **user_parsed = my_str_to_word_array(usr[0]);
        if (strcmp(user_parsed[0], "##USER") == 0) {
            current_client->username = strdup(user_parsed[1]);
            i++;
            continue;
        }
        if (strcmp(user_parsed[0], "##UUID") == 0) {
            current_client->uuid_text = strdup(user_parsed[1]);
            i++;
            continue;
        }
    }
    current_client->already_subscribed = true;
    replace_line_file("##STATUS 0", "##STATUS 1",
    strcat(file, current_client->uuid_text));
}

void execute_function_login(server **serv, client *current_client, int i)
{
    void *function;
    if (i == 0) {
        function = load_library_function((*serv)->lib,
        "server_event_user_created");
        ((void (*)(char const *, char const *))function)
        (current_client->uuid_text, current_client->username);
    } else if (i == 1) {
        function = load_library_function((*serv)->lib,
        "server_event_user_logged_in");
        ((void (*)(char *))function)(current_client->uuid_text);
    }
}

// ? free(file);
void login_handler(server **serv, client *cur_client, int sd)
{
    char **usr, str[1024];
    char *file = malloc(sizeof(char) * 1024); strcpy(file, "data/users/");
    if (args_check((*serv)->command, 2, sd) == false ||
    user_connected(cur_client) == true) return;
    if ((usr = read_folder_files(file, (*serv)->command[1])) != NULL) {
        parse_user_data_login(usr, cur_client);
        sprintf(str, "##UUID %s\n##USER %s\n", cur_client->uuid_text,
        cur_client->username);
    } else {
        cur_client->username = strdup((*serv)->command[1]);
        uuid_generate(cur_client->uuid);
        uuid_unparse(cur_client->uuid, cur_client->uuid_text);
        execute_function_login(serv, cur_client, 0);
        sprintf(str, "##UUID %s\n##USER %s\n##STATUS 1", cur_client->uuid_text,
        cur_client->username);
        write_in_file(strcat(file, cur_client->uuid_text), str);
    }
    cur_client->is_logged = true;
    execute_function_login(serv, cur_client, 1);
    send(sd, str, strlen(str), 0);
}
