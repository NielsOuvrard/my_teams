/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int unknown_team_function   (client *cli, char **array)
{
    return client_error_unknown_team(array[1]);
}

int unknown_channel_function(client *cli, char **array)
{
    return client_error_unknown_channel(array[1]);
}

int unknown_thread_function (client *cli, char **array)
{
    return client_error_unknown_thread(array[1]);
}

int unknown_user_function   (client *cli, char **array)
{
    return client_error_unknown_user(array[1]);
}

int unauthorized_function   (client *cli, char **array)
{
    return client_error_unauthorized();
}
