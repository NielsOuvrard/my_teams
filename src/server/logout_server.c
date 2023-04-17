/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my_server.h"

// CODE_202 = "202 Logged out."
int logout_handler(server **serv, client *cur_cli, int sd)
{
    if (!args_check((*serv)->command, 1, sd) || user_not_connected(cur_cli))
        return 1;
    change_status_user(serv, cur_cli->uuid_text, 0);
    server_event_user_logged_out(cur_cli->uuid_text);
    char *to_send = malloc(sizeof(char) * 1024);
    sprintf(to_send, "%s\n%s\n%s\n", CODE_202, cur_cli->uuid_text,
    cur_cli->username);
    send(sd, to_send, strlen(to_send) + 1, 0);
    free(to_send);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    return 0;
}
