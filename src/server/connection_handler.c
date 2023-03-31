/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my.h"

void logout_handler(server **serv, client *cur_cli, int sd)
{
    if (args_check((*serv)->command, 1, sd) == false)
        return;
    if (user_not_connected(cur_cli) == true)
        return;
    void *function =
    load_library_function((*serv)->lib, "server_event_user_logged_out");
    ((void (*)(char *))function)(cur_cli->uuid_text);
    send(sd, "200 Logout ok.\n", 15, 0);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    char *file_path = malloc(strlen(cur_cli->uuid_text) + 13);
    strcat(file_path, "data/users/");
    strcat(file_path, cur_cli->uuid_text);
    replace_line_file("##STATUS 1", "##STATUS 0", file_path);
    remove_client(cur_cli, sd);
}

void parse_user_data_login(char **usr, client *cur_cli)
{
    for (int i = 0; usr[i] != NULL; i++) {
        char **user_parsed = my_str_to_word_array(usr[0]);
        if (strcmp(user_parsed[0], "##USER") == 0) {
            cur_cli->username = strdup(user_parsed[1]);
            i++;
            continue;
        }
        if (strcmp(user_parsed[0], "##UUID") == 0) {
            cur_cli->uuid_text = strdup(user_parsed[1]);
            i++;
            continue;
        }
    }
    cur_cli->already_subscribed = true;
    char *file_path = malloc(strlen(cur_cli->uuid_text) + 13);
    strcat(file_path, "data/users/");
    strcat(file_path, cur_cli->uuid_text);
    replace_line_file("##STATUS 0", "##STATUS 1", file_path);
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
    char *file = malloc(sizeof(char) * 1024);
    strcpy(file, "data/users/");
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
