/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int messages_function       (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    messages_handler(serv, cli_list, curr_cli, sd);
    return 0;
}

bool user_not_subscribed(server **se, client *cli, char *team_uuid,
sqlite3 *db)
{
    sqlite3_prepare_v2(db, "SELECT user_uuids FROM teams WHERE uuid = ?;",
    -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, team_uuid, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    if (user_uuids == NULL || strstr(user_uuids, cli->uuid_text) == NULL) {
        sqlite3_finalize((*se)->stmt);
        send(cli->socket, CODE_504, strlen(CODE_504) + 1, 0);
        sqlite3_finalize((*se)->stmt);
        return true;
    }
    sqlite3_finalize((*se)->stmt);
    return false;
}

int subscribed_function     (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int unsubscribe_function    (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    if (user_not_connected(current_client) || !args_check((*serv)->command, 2, sd))
        return 0;
    char to_send[1024] = {0};
    if (!check_if_uuid_exists((*serv)->command[1], "teams", (*serv)->db)) {
        strcpy(to_send, CODE_500); strcat(to_send, current_client->team);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    sqlite3_prepare_v2((*serv)->db, "SELECT user_uuids FROM teams WHERE uuid = ?;", -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, (*serv)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*serv)->stmt, 0);
    char new_user_uuids[4096];
    sprintf(new_user_uuids, "%s", user_uuids);
    char *token = strtok(new_user_uuids, ",");
    char *tmp = NULL;
    while (token != NULL) {
        if (strcmp(token, current_client->uuid_text) != 0) {
            if (tmp == NULL)
                sprintf(tmp, "%s", token);
            else
                sprintf(tmp, "%s,%s", tmp, token);
        }
        token = strtok(NULL, ",");
    }
    sqlite3_finalize((*serv)->stmt);
    sqlite3_prepare_v2((*serv)->db, "UPDATE teams SET user_uuids = ? WHERE uuid = ?;", -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1, tmp, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, (*serv)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    sqlite3_finalize((*serv)->stmt);
    return 0;
}

// [“team_uuid”] ? [“channel_uuid”] ? [“thread_uuid”]
int use_function            (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli))
        return 0;
    curr_cli->team = NULL;
    curr_cli->channel = NULL;
    curr_cli->thread = NULL;
    if (args_check((*serv)->command, 2, sd))
        curr_cli->team = strdup((*serv)->command[1]);
    if (args_check((*serv)->command, 3, sd))
        curr_cli->channel = strdup((*serv)->command[2]);
    if (args_check((*serv)->command, 4, sd))
        curr_cli->thread = strdup((*serv)->command[3]);
    return 0;
}
