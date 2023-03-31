/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int login_function          (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    login_handler(serv, current_client, sd);
    return 0;
}

int logout_function         (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    logout_handler(serv, current_client, sd);
    return 0;
}

int users_function          (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    users_list_handler(serv, cli_list, current_client, sd);
    return 0;
}

int user_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    user_list_handler(serv, cli_list, current_client, sd);
    return 0;
}

int send_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}
