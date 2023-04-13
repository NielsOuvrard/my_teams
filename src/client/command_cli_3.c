/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

// did we send the type of create ?
// 1 = team
// 2 = channel
// 3 = thread
int create_function         (client *cli, char **array)
{
    if (array[1] == NULL || array[2] == NULL)
        return 0;
    if (!strncmp(array[1], "1", 2)) {
        client_event_team_created(array[2], array[3], array[4]);
    } else if (!strncmp(array[1], "2", 2)) {
        client_event_channel_created(array[2], array[3], array[4]);
    } else if (!strncmp(array[1], "3", 2)) {
        client_event_thread_created(array[2], array[3], /* time */0, array[5], array[6]);
    }
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
