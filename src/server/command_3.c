/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int create_function         (server **se, client **cli_list,
                            client *cli, int sd)
{
    return create_handler(se, cli_list, cli, sd);
}

int list_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int info_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int help_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    send(sd, CODE_200, strlen(CODE_200), 0);
    return 0;
}
