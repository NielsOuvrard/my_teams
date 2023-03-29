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
    if (user_not_connected(current_client) == true)
        return;
    void *function =
    load_library_function((*serv)->lib, "server_event_user_logged_out");
    ((void (*)(char *))function)(current_client->uuid_text);
    send(sd, "200 Logout ok.\n", 15, 0);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    remove_client(current_client, sd);
}

void check_if_login_with_existing_user(server **serv,
client *current_client, int sd)
{
    current_client->username = strdup((*serv)->command[1]);
    current_client->is_logged = true;
    for (int i = 0; i != MAX_CLIENTS; i++) {
        if ((*serv)->saved_cli[i].username != NULL &&
        strcmp((*serv)->saved_cli[i].username, (*serv)->command[1]) == 0) {
            current_client->uuid_text = strdup((*serv)->saved_cli[i].uuid_text);
            current_client->already_subscribed = true;
            return;
        }
    }
    uuid_generate(current_client->uuid);
    uuid_unparse(current_client->uuid, current_client->uuid_text);
}

void login_handler(server **serv, client *current_client, int sd)
{
    char str[100];
    if (args_check((*serv)->command, 2, sd) == false ||
    user_connected(current_client) == true)
        return;
    check_if_login_with_existing_user(serv, current_client, sd);
    void *function;
    sprintf(str, "##UUID %s ##USER %s\n",
    current_client->uuid_text, current_client->username);
    if (check_user_already_subscribed(current_client) == false) {
        function =
        load_library_function((*serv)->lib, "server_event_user_created");
        ((void (*)(char *, char *))function)(current_client->uuid_text,
        (*serv)->command[1]);
        write_in_file("./data/.users", str);
    }
    function = load_library_function((*serv)->lib,
    "server_event_user_logged_in");
    ((void (*)(char *))function)(current_client->uuid_text);
    send(sd, str, strlen(str), 0);
}
