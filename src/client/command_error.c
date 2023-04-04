/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int unknown_team_function   (client *cli, char **array)
{
    fct_1 function = cli->data_lib[13].fct;
    return function(array[1]);
}

int unknown_channel_function(client *cli, char **array)
{
    fct_1 function = cli->data_lib[14].fct;
    return function(array[1]);
}

int unknown_thread_function (client *cli, char **array)
{
    fct_1 function = cli->data_lib[15].fct;
    return function(array[1]);
}

int unknown_user_function   (client *cli, char **array)
{
    fct_1 function = cli->data_lib[16].fct;
    return function(array[1]);
}

int unauthorized_function   (client *cli, char **array)
{
    fct_0 function = cli->data_lib[17].fct;
    return function();
}
