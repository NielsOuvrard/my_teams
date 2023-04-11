/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** save_message
*/

#include "my_server.h"

void save_message_in_db(server **serv, client *curr_cli)
{
    char request[1024], timeStamp[20];
    time_t now = time(NULL);
    strftime(timeStamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    sqlite3_prepare_v2((*serv)->messages_db,
    "INSERT INTO messages (sender, receiver, message, timestamp) \
    VALUES (?, ?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, curr_cli->uuid_text, -1, NULL);
    sqlite3_bind_text((*serv)->stmt, 2, (*serv)->command[1], -1, NULL);
    sqlite3_bind_text((*serv)->stmt, 3, (*serv)->command[2], -1, NULL);
    sqlite3_bind_text((*serv)->stmt, 4, timeStamp, -1, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
}
