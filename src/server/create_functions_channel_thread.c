/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** create_handler
*/

#include "my_server.h"

char *channel_message_to_everyone(char *uuid, char *name, char *description)
{
    char *to_send = malloc(sizeof(char) * 1024);
    strcpy(to_send, CODE_214);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, name); strcat(to_send, "\n");
    strcat(to_send, description); strcat(to_send, "\n");
    return to_send;
}

char *create_channel         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    if (user_not_connected(cur_cli) || !args_check((*serv)->command, 3, sd))
        return 0;
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
    char to_send[1024];
    sprintf(to_send, "%s%s\n%s\n%s\n", CODE_213, uuid, name, description);
    server_event_channel_created(team_uuid, uuid, name);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return channel_message_to_everyone(uuid, name, description);
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

char *thread_message_to_everyone(char *to_send, char *timeStamp, char *title,
char *body)
{
    strcat(to_send, timeStamp);
    strcat(to_send, title); strcat(to_send, "\n");
    strcat(to_send, body); strcat(to_send, "\n");
    return to_send;
}

char *create_thread         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    if (user_not_connected(cur_cli) || !args_check((*serv)->command, 3, sd))
        return 0;
    char *uuid = generate_uuid(), *title = (*serv)->command[1];
    char *body = (*serv)->command[2], *channel_uuid = cur_cli->channel;
    char *timeStamp, *user_uuid = cur_cli->uuid_text;
    time_t now = time(NULL);
    timeStamp = ctime(&now);
    create_thread_sql(serv, cur_cli, timeStamp, uuid);
    char to_send[1024];
    sprintf(to_send, "%s%s\n%s\n%s%s\n%s\n", CODE_215, uuid, user_uuid,
    timeStamp, title, body);
    server_event_thread_created(channel_uuid, uuid, user_uuid,
    title, body);
    send(sd, to_send, strlen(to_send) + 1, 0);
    memset(to_send, 0, 1024);
    sprintf(to_send, "%s%s\n%s\n", CODE_216, uuid, user_uuid);
    return thread_message_to_everyone(to_send, timeStamp, title, body);
}
