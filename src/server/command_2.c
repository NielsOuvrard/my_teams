/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int messages_function       (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    messages_handler(serv, cli_list, curr_cli, sd);
    return 0;
}

int subscribe_function      (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int subscribed_function     (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int unsubscribe_function    (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

// [“team_uuid”] ? [“channel_uuid”] ? [“thread_uuid”]
int use_function            (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli))
        return 0;
    curr_cli->team = NULL;
    curr_cli->channel = NULL;
    curr_cli->thread = NULL;
    curr_cli->team = (*serv)->command[1];
    curr_cli->channel = (*serv)->command[2];
    curr_cli->thread = (*serv)->command[3];
    return 0;
}
