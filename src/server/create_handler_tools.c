/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** context_handler
*/

#include "my_server.h"

void send_message_to_every_one(server **se, client **cli_list,
client *cli, char *message)
{
    sqlite3_prepare_v2((*se)->db,
    "SELECT user_uuids FROM teams WHERE uuid = ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, cli->team, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (strstr(message, "211") && (*cli_list)[i].socket != -1 &&
        (*cli_list)[i].is_logged) {
            send((*cli_list)[i].socket, message, strlen(message) + 1, 0);
        } else if ((*cli_list)[i].socket != -1 && (*cli_list)[i].is_logged &&
        strstr(user_uuids, (*cli_list)[i].uuid_text)) {
            send((*cli_list)[i].socket, message, strlen(message) + 1, 0);
        }
    }
    sqlite3_finalize((*se)->stmt);
}

char *send_code_and_value(char *code, char *value, int sd)
{
    char to_send[1024];
    strcpy(to_send, code);
    strcat(to_send, value);
    strcat(to_send, "\n");
    send(sd, to_send, strlen(to_send) + 1, 0);
    return "error";
}
