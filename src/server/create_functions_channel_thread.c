/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** create_handler
*/

#include "my_server.h"

char *create_channel         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    char *uuid = generate_uuid(), *name = (*serv)->command[1];
    char *description = (*serv)->command[2], *team_uuid = cur_cli->team;
    sqlite3_prepare_v2((*serv)->db,
    "INSERT INTO channels (uuid, team, name, description)\
    VALUES (?, ?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, team_uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 3, name, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 4, description, -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    char *to_send = malloc(sizeof(char) * 1024);
    strcpy(to_send, CODE_212);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, name); strcat(to_send, "\n");
    strcat(to_send, description); strcat(to_send, "\n");
    server_event_channel_created(team_uuid, uuid, name);
    return to_send;
}

void create_thread_sql (server **se, client *cur_cli,
char *timeStamp, char *uuid)
{
    sqlite3_prepare_v2((*se)->db, "INSERT INTO threads (uuid, channel, \
user, title, body, timestamp) VALUES (?, ?, ?, ?, ?, ?);",
    -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 2, cur_cli->channel, -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 3, cur_cli->uuid_text, -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 4, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 5, (*se)->command[2], -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 6, timeStamp, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    sqlite3_finalize((*se)->stmt);
}

char *create_thread         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    char *uuid = generate_uuid(), *title = (*serv)->command[1];
    char *body = (*serv)->command[2], *channel_uuid = cur_cli->channel;
    char *timeStamp, *user_uuid = cur_cli->uuid_text;
    time_t now = time(NULL);
    timeStamp = ctime(&now);
    create_thread_sql(serv, cur_cli, timeStamp, uuid);
    char *to_send = malloc(sizeof(char) * 1024);
    strcpy(to_send, CODE_213);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, user_uuid); strcat(to_send, "\n");
    strcat(to_send, timeStamp);
    strcat(to_send, title); strcat(to_send, "\n");
    strcat(to_send, body); strcat(to_send, "\n");
    server_event_thread_created(channel_uuid, uuid, user_uuid,
    title, body);
    return to_send;
}
