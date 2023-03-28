/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my.h"

void logout_handler(server **serv, client *current_client, int sd)
{
    if (args_check((*serv)->command, 1, sd) == false)
        return;
    void *function =
    load_library_function((*serv)->lib, "server_event_user_logged_out");
    ((void (*)(char *))function)(current_client->uuid_text);
    send(sd, "200 Logout ok.\n", 15, 0);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    remove_client(current_client, sd);
}

void login_handler(server **serv, client *current_client, int sd)
{
    if (args_check((*serv)->command, 2, sd) == false)
        return;
    if (user_connected(current_client, (*serv)->command[1]) == true)
        return;
    else {
        void *function =
        load_library_function((*serv)->lib, "server_event_user_created");
        ((void (*)(char *, char *))function)(current_client->uuid_text,
        (*serv)->command[1]);
        current_client->username = strdup((*serv)->command[1]);
        current_client->is_logged = true;
        send(sd, "331 Login ok need password.\n", 28, 0);
    }
}
