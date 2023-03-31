/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** infos_users_handler
*/

#include "my.h"

void users_list_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    char str[1024];
    if (user_not_connected(current_client) == true)
        return;
    get_folder_files(*serv, "data/users/", NULL, sd,
    "send");
}
