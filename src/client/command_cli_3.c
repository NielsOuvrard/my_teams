/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int create_function         (client *cli, char **array)
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
    fct_0 function = cli->data_lib[18].fct;
    return function();
}
