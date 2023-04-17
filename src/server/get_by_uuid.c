/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** get_by_uuid
*/

#include "my_server.h"

// looking for into sqlite3 database
char *get_team_by_uuid (server **se, char *uuid)
{
    int result = sqlite3_prepare_v2((*se)->db,
    "SELECT * FROM teams WHERE uuid = ?;", -1, &(*se)->stmt, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize((*se)->stmt);
        fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*se)->db));
        return NULL;
    }
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    if (sqlite3_step((*se)->stmt) == SQLITE_ROW) {
        char *ret = strdup(sqlite3_column_text((*se)->stmt, 0));
        sqlite3_finalize((*se)->stmt);
        return ret;
    }
    sqlite3_finalize((*se)->stmt);
    return NULL;
}

char *get_channel_by_uuid (server **se, char *team_uuid, char *channel_uuid)
{
    int result = sqlite3_prepare_v2((*se)->db,
    "SELECT * FROM channels WHERE uuid = ? AND uuid_team = ?;", -1,
    &(*se)->stmt, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*se)->db));
        return NULL;
    }
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[2], -1, SQLITE_STATIC);
    if (sqlite3_step((*se)->stmt) == SQLITE_ROW) {
        char *ret = strdup(sqlite3_column_text((*se)->stmt, 0));
        sqlite3_finalize((*se)->stmt);
        return ret;
    }
    sqlite3_finalize((*se)->stmt);
    return NULL;
}
// uuid_team TEXT, uuid_channel TEXT, uuid TEXT, name TEXT, description TEXT
char *get_thread_by_uuid (server **se, char *team, char *cha, char *thr)
{
    int result = sqlite3_prepare_v2((*se)->db, "SELECT * FROM threads WHERE \
uuid = ? AND uuid_team = ? AND uuid_channel = ?;",
    -1, &(*se)->stmt, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*se)->db));
        return NULL;
    }
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[2], -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[3], -1, SQLITE_STATIC);
    if (sqlite3_step((*se)->stmt) == SQLITE_ROW) {
        char *ret = strdup(sqlite3_column_text((*se)->stmt, 0));
        sqlite3_finalize((*se)->stmt);
        return ret;
    }
    sqlite3_finalize((*se)->stmt);
    return NULL;
}
