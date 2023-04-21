/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

bool user_already_subscribed(server **se, client *cli, char *team_uuid,
sqlite3 *db)
{
    sqlite3_prepare_v2(db, "SELECT user_uuids FROM teams WHERE uuid = ?;",
    -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, team_uuid, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    if (user_uuids == NULL) {
        sqlite3_finalize((*se)->stmt);
        return false;
    }
    if (strstr(user_uuids, cli->uuid_text)) {
        send(cli->socket, CODE_230, strlen(CODE_230) + 1, 0);
        sqlite3_finalize((*se)->stmt);
        return true;
    }
    sqlite3_finalize((*se)->stmt);
    return false;
}

void subscribe_sql_commands (server **se, client **cli_list,
client *cli, int sd)
{
    sqlite3_prepare_v2((*se)->db, "SELECT user_uuids FROM teams WHERE uuid\
= ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    char new_user_uuids[4096];
    if (user_uuids == NULL)
        sprintf(new_user_uuids, "%s", cli->uuid_text);
    else
        sprintf(new_user_uuids, "%s,%s", user_uuids, cli->uuid_text);
    sqlite3_finalize((*se)->stmt);
    sqlite3_prepare_v2((*se)->db, "UPDATE teams SET user_uuids = ? WHERE \
uuid = ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, new_user_uuids, -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 2, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    sqlite3_finalize((*se)->stmt);
}

int subscribe_function      (server **se, client **cli_list,
                            client *cli, int sd)
{
    if (user_not_connected(cli) || !args_check((*se)->command, 2, sd))
        return 0;
    char to_send[1024] = {0};
    if (!check_if_uuid_exists((*se)->command[1], "teams", (*se)->db)) {
        strcpy(to_send, CODE_500); strcat(to_send, cli->team);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    if (user_already_subscribed(se, cli, (*se)->command[1], (*se)->db)) {
        return 0;
    }
    subscribe_sql_commands(se, cli_list, cli, sd);
    strcpy(to_send, CODE_207); strcat(to_send, cli->uuid_text);
    strcat(to_send, "\n"); strcat(to_send, (*se)->command[1]);
    strcat(to_send, "\n");
    server_event_user_subscribed((*se)->command[1], cli->uuid_text);
    send_message_to_every_one(se, cli_list, cli, to_send);
    return 0;
}
