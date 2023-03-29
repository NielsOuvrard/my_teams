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
    for (int i = 0; i != MAX_CLIENTS; i++) {
        if ((*cli_list)[i].socket != -1 || (*cli_list)[i].username != NULL) {
            sprintf(str, "##USER %s ##UUID %s ##STATUS %d",
            (*cli_list)[i].username, (*cli_list)[i].uuid_text,
            (*cli_list)[i].is_logged);
            send(sd, str, strlen(str), 0);
            printf("%s\n", str);
        }
    }
}
