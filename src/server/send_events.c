/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** send_events
*/

#include "my_server.h"

void send_event_logged_in(server **serv, client **cli_list,
client *current_client, int sd)
{
    char to_send[4096];
    strcpy(to_send, CODE_201);
    strcat(to_send, current_client->uuid_text);
    strcat(to_send, "\n");
    strcat(to_send, current_client->username);
    strcat(to_send, "\n");
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ((*cli_list)[i].socket != -1 && (*cli_list)[i].socket != sd
        && (*cli_list)[i].is_logged) {
            send((*cli_list)[i].socket, to_send, strlen(to_send) + 1, 0);
        }
    }
}

void send_event_logged_out(server **serv, client **cli_list,
client *current_client, int sd)
{
    char to_send[4096];
    strcpy(to_send, CODE_202);
    strcat(to_send, current_client->uuid_text);
    strcat(to_send, "\n");
    strcat(to_send, current_client->username);
    strcat(to_send, "\n");
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if ((*cli_list)[i].socket != -1 && (*cli_list)[i].socket != sd
        && (*cli_list)[i].is_logged) {
            send((*cli_list)[i].socket, to_send, strlen(to_send) + 1, 0);
        }
    }
}
