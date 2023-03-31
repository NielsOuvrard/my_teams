/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** infos_users_handler
*/

#include "my_server.h"

void user_list_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    if (user_not_connected(current_client) == true ||
    args_check((*serv)->command, 2, sd) == false)
        return;
    (*serv)->to_do = strdup("send");
    char **usr = read_folder_files("data/users/", (*serv)->command[1]);
    if (usr == NULL) {
        send(sd, "590 User not found.\n", 20, 0);
        return;
    }
    send_info(usr, sd);
}

// CODE_400
void users_list_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    if (user_not_connected(current_client) == true ||
    args_check((*serv)->command, 1, sd) == false)
        return;
    (*serv)->to_do = strdup("send");
    get_folder_files(*serv, "data/users/", NULL, sd);
}
