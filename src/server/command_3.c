/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

char *generate_uuid(void)
{
    uuid_t uuid;
    uuid_generate(uuid);
    char *uuid_text = malloc(sizeof(uuid_t) * 2 + 5);
    uuid_unparse(uuid, uuid_text);
    return uuid_text;
}

int create_team         (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    char *uuid = generate_uuid();
    char *name = (*serv)->command[1];
    char *description = (*serv)->command[2];
    sqlite3_prepare_v2((*serv)->teams_db,
    "INSERT INTO teams (uuid, name, description) VALUES (?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, name, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 3, description, -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    char to_send[1024];
    strcpy(to_send, CODE_211);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, name); strcat(to_send, "\n");
    strcat(to_send, description); strcat(to_send, "\n");
    server_event_team_created(uuid, name, curr_cli->uuid_text);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int create_channel         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    char *uuid = generate_uuid(), *name = (*serv)->command[1];
    char *description = (*serv)->command[2], *team_uuid = cur_cli->team_uuid;
    sqlite3_prepare_v2((*serv)->channels_db,
    "INSERT INTO channels (uuid, team, name, description) VALUES (?, ?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, team_uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 3, name, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 4, description, -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    char to_send[1024];
    //change code in my.h
    strcpy(to_send, CODE_212);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, name); strcat(to_send, "\n");
    strcat(to_send, description); strcat(to_send, "\n");
    server_event_channel_created(team_uuid, uuid, name);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int create_thread         (server **serv, client **cli_list,
                            client *cur_cli, int sd)
{
    char *uuid = generate_uuid(), *title = (*serv)->command[1];
    char *body = (*serv)->command[2], *channel_uuid = cur_cli->channel_uuid;
    char timeStamp[20], *user_uuid = cur_cli->uuid_text;
    time_t now = time(NULL);
    strftime(timeStamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    sqlite3_prepare_v2((*serv)->threads_db,
    "INSERT INTO threads (uuid, channel, user, title, body, timestamp) VALUES (?, ?, ?, ?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, channel_uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 3, user_uuid, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 4, title, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 5, body, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 6, timeStamp, -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    char to_send[1024];
    strcpy(to_send, CODE_213);
    strcat(to_send, uuid); strcat(to_send, "\n");
    strcat(to_send, user_uuid); strcat(to_send, "\n");
    strcat(to_send, timeStamp); strcat(to_send, "\n");
    strcat(to_send, title); strcat(to_send, "\n");
    strcat(to_send, body); strcat(to_send, "\n");
    server_event_thread_created(channel_uuid, uuid, user_uuid,
    title, body);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int create_function         (server **se, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli))
        return 0;
    if (args_check((*se)->command, 2, sd) && curr_cli->context != REPLY) {
        send(sd, CODE_590, strlen(CODE_590) + 1, 0);
        return 0;
    } else {
        // create_reply(se, cli_list, curr_cli, sd);
    }
    if (!args_check((*se)->command, 3, sd)) {
        send(sd, CODE_590, strlen(CODE_590) + 1, 0);
        return 0;
    }
    if (curr_cli->context == TEAM) {
        if (check_if_name_exists((*se)->command[1], "teams", (*se)->teams_db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return 0;
        } else {
            create_team(se, cli_list, curr_cli, sd);
        }
    } else if (curr_cli->context == CHANNEL) {
        if (check_if_name_exists((*se)->command[1],
        "channels", (*se)->channels_db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return 0;
        } else {
            create_channel(se, cli_list, curr_cli, sd);
        }
    } else {
        if (check_if_name_exists((*se)->command[1],
        "threads", (*se)->threads_db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return 0;
        } else {
            create_thread(se, cli_list, curr_cli, sd);
        }
    }
    return 0;
}

int list_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int info_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int help_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    send(sd, CODE_200, strlen(CODE_200), 0);
    return 0;
}
