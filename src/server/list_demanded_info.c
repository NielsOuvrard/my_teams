/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** preload_users
*/

#include "my_server.h"

int find_message_receiver(server **serv, client **clients)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ((*clients)[i].is_logged && strcmp((*clients)[i].uuid_text,
        (*serv)->command[1]) == 0) {
            return (*clients)[i].socket;
        }
    }
    return -1;
}
