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

int use_function            (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}
