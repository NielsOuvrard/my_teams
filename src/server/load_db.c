/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** load_db
*/

#include "my_server.h"

void initialize_thread_db(server **serv)
{
    int result;
    if (sqlite3_open("data/threads.db", &(*serv)->threads_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->threads_db, CREATE_THREADS_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void initialize_channel_db(server **serv)
{
    int result;
    if (sqlite3_open("data/channels.db", &(*serv)->channels_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->channels_db, CREATE_CHANNELS_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void initialize_teams_db(server **serv)
{
    int result;
    if (sqlite3_open("data/teams.db", &(*serv)->teams_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->teams_db, CREATE_TEAMS_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void initialize_message_db(server **serv)
{
    int result;
    if (sqlite3_open("data/messages.db", &(*serv)->messages_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->messages_db, CREATE_MESSAGES_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void initialize_user_db(server **serv)
{
    int result;
    if (sqlite3_open("data/users.db", &(*serv)->users_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->users_db, CREATE_USER_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void initialize_db(server **serv)
{
    initialize_user_db(serv);
    initialize_message_db(serv);
    initialize_teams_db(serv);
    initialize_channel_db(serv);
    initialize_thread_db(serv);
}
