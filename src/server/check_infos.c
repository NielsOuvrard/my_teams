/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** load_infos
*/

#include "my_server.h"

bool check_if_name_exists(char *name, char *table, sqlite3 *db)
{
    sqlite3_stmt *stmt;
    char *query = malloc(sizeof(char) * 100);
    strcpy(query, "SELECT name FROM ");
    strcat(query, table);
    strcat(query, " WHERE name = ?;");
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool check_if_uuid_exists(char *uuid, char *table, sqlite3 *db)
{
    sqlite3_stmt *stmt;
    char *query = malloc(sizeof(char) * 100);
    strcpy(query, "SELECT uuid FROM ");
    strcat(query, table);
    strcat(query, " WHERE uuid = ?;");
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, uuid, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool check_if_user_exist(server **se, int sd)
{
    char to_send[4096];
    strcpy(to_send, CODE_503);
    strcat(to_send, (*se)->command[1]);
    int result = sqlite3_prepare_v2((*se)->db,
    "SELECT COUNT(*) FROM users WHERE uuid = ?;", -1,
    &(*se)->stmt, NULL);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*se)->db));
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    if (sqlite3_step((*se)->stmt) == SQLITE_ROW)
        result = sqlite3_column_int((*se)->stmt, 0);
    if (result > 0) {
        return true;
    } else {
        send(sd, to_send, strlen(to_send) + 1, 0);
        return false;
    }
}

int find_message_receiver(server **serv, client **clients)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (strcmp((*clients)[i].uuid_text,
        (*serv)->command[1]) == 0) {
            return (*clients)[i].socket;
        }
    }
    return -1;
}
