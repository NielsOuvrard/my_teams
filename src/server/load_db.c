/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** load_db
*/

#include "my_server.h"

int initialize_db_2(server **serv)
{
    sqlite3_prepare_v2((*serv)->db, CREATE_CHANNELS_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    sqlite3_prepare_v2((*serv)->db, CREATE_THREADS_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    sqlite3_prepare_v2((*serv)->db, CREATE_REPLIES_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    return 1;
}

int initialize_db(server **serv)
{
    if (sqlite3_open("data/data.db", &(*serv)->db) != SQLITE_OK) {
        error_sql(*serv, "Can't open database: %s\n");
        sqlite3_close((*serv)->db);
        return -1;
    }
    sqlite3_prepare_v2((*serv)->db, CREATE_USERS_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    sqlite3_prepare_v2((*serv)->db, CREATE_MESSAGES_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    sqlite3_prepare_v2((*serv)->db, CREATE_TEAMS_DB, -1,
    &(*serv)->stmt, NULL);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    return initialize_db_2(serv);
}
