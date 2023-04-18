/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int create_team_function    (client *cli, char **array)
{
    if (array[1] == NULL || array[2] == NULL || array[3] == NULL)
        return 0;
    client_event_team_created(array[1], array[2], array[3]);
    return 0;
}

int create_channel_function (client *cli, char **array)
{
    if (array[1] == NULL || array[2] == NULL || array[3] == NULL)
        return 0;
    client_event_channel_created(array[1], array[2], array[3]);
    return 0;
}

int create_thread_function  (client *cli, char **array)
{
    if (array[1] == NULL || array[2] == NULL ||
    array[3] == NULL || array[4] == NULL)
        return 0;
    struct tm tm;
    strptime(array[3], "%a %b %d %H:%M:%S %Y", &tm);
    time_t t = mktime(&tm);
    if (t == -1) {
        return 0;
    }
    client_event_thread_created(array[1], array[2], t, array[3], array[4]);
    return 0;
}
