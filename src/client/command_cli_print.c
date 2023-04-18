/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int print_team_function     (client *cli, char **array)
{
    client_print_teams(array[1], array[2], array[3]);
    return 0;
}

int print_channel_function  (client *cli, char **array)
{
    client_team_print_channels(array[1], array[2], array[3]);
    return 0;
}

int print_thread_function   (client *cli, char **array)
{
    client_channel_print_threads(array[1], array[2], /**/ 0,
    array[4], array[5]);
    return 0;
}

int print_reply_function    (client *cli, char **array)
{
    client_thread_print_replies(array[1], array[2], /**/0, array[4]);
    return 0;
}
