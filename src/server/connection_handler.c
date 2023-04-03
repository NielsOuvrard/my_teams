/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my_server.h"

// CODE_202 = "202 Logged out."
// 9 = server_event_user_logged_out
void logout_handler(server **serv, client *cur_cli, int sd)
{
    if (!args_check((*serv)->command, 1, sd) || user_not_connected(cur_cli))
        return;
    fct_1 function = (*serv)->array_fct[9];
    function(cur_cli->uuid_text);
    char *to_send = malloc(sizeof(char) * 1024);
    sprintf(to_send, "%s\n%s\n%s", CODE_202, cur_cli->uuid_text,
    cur_cli->username);
    send(sd, to_send, strlen(to_send), 0);
    free(to_send);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    cur_cli->is_logged = false;
}

// 6 "server_event_user_created"
// 8 "server_event_user_logged_in"
void execute_function_login(server **serv, client *current_client, int i)
{
    void *function;
    if (i == 0) {
        fct_2 function = (*serv)->array_fct[6];
        function(current_client->uuid_text, current_client->username);
    } else if (i == 1) {
        fct_1 function = (*serv)->array_fct[8];
        function(current_client->uuid_text);
    }
}

// ? free(file);
// printf("Send to client : |%s|\n", str);
void login_handler(server **serv, client *cli, int sd)
{
    char **usr, str[1024], *filename = NULL, *file = malloc(1024);
    strcpy(file, "data/users/");
    if (!args_check((*serv)->command, 2, sd) || user_connected(cli))
        return;
    if ((usr = read_folder_files(file, (*serv)->command[1], &filename))) {
        cli->uuid_text = filename;
        cli->username = strdup(usr[0]);
        free_my_array(usr);
        sprintf(str, "%s\n%s\n%s\n", CODE_201, cli->uuid_text, cli->username);
    } else {
        cli->username = strdup((*serv)->command[1]);
        uuid_generate(cli->uuid);
        uuid_unparse(cli->uuid, cli->uuid_text);
        execute_function_login(serv, cli, 0);
        write_in_file(strcat(file, cli->uuid_text), cli->username);
        sprintf(str, "%s\n%s\n%s\n", CODE_201, cli->uuid_text, cli->username);
    }
    cli->is_logged = true;
    execute_function_login(serv, cli, 1);
    send(sd, str, strlen(str), 0);
}
