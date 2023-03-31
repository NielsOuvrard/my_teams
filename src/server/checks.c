/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** user_check
*/

#include "my_server.h"

bool args_check(char **command, int nb_args, int sd)
{
    int i = 0;

    while (command[i] != NULL)
        i++;
    if (i != nb_args) {
        send(sd, "590 Invalid command.\n", 21, 0);
        return false;
    }
    return true;
}

bool user_connected(client *current_client)
{
    if (current_client->is_logged == true) {
        send(current_client->socket, "200 User already logged in.\n", 28, 0);
        return true;
    }
    return false;
}

bool user_not_connected(client *current_client)
{
    if (current_client->is_logged == false) {
        send(current_client->socket, "210 U need to be connect.\n", 23, 0);
        return true;
    }
    return false;
}

bool check_user_already_subscribed(client *current_client)
{
    if (current_client->already_subscribed == true) {
        send(current_client->socket, "205 already subscribed.\n", 24, 0);
        return true;
    }
    return false;
}
