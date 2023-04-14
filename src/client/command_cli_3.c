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
    if (array[1] == NULL || array[2] == NULL || array[3] == NULL || array[4] == NULL)
        return 0;
    client_event_thread_created(array[1], array[2], /* time */0, array[3], array[4]);
    return 0;
}

int create_reply_function   (client *cli, char **array)
{
    return 0;
}

int list_function           (client *cli, char **array)
{
    return 0;
}

int info_function           (client *cli, char **array)
{
    return 0;
}

int help_function           (client *cli, char **array)
{
    printf("list commandes :\n\thelp\n\tlogin\n\t\
logout\n\tusers\n\tuser\n\tsend\n\tmessages\n\t\
subscribe\n\tsubscribed\n\tunsubscribe\n\tuse\n\t\
create\n\tlist\n\tinfo\n");
    return 0;
}

int already_exist_function  (client *cli, char **array)
{
    return client_error_already_exist();
}
