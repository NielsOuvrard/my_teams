/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_unsubscribe
*/

#include "my_server.h"

char *get_new_format(char *tmp, char *token)
{
    if (tmp == NULL)
        sprintf(tmp, "%s", token);
    else
        sprintf(tmp, "%s,%s", tmp, token);
    return tmp;
}

char *get_new_user_uuids(char *user_uuids, char *uuid)
{
    char new_user_uuids[4096];
    sprintf(new_user_uuids, "%s", user_uuids);
    char *token = strtok(new_user_uuids, ",");
    char *tmp = malloc(sizeof(char) * 4096);
    while (token != NULL) {
        if (strcmp(token, uuid) != 0) {
            tmp = get_new_format(tmp, token);
        }
        token = strtok(NULL, ",");
    }
    return tmp;
}

void unsubscribe_sql_commands (server **se, client **cli_list,
client *cli, int sd)
{
    sqlite3_prepare_v2((*se)->db, "SELECT user_uuids FROM teams WHERE uuid = ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    char *tmp = get_new_user_uuids(user_uuids, cli->uuid_text);
    sqlite3_finalize((*se)->stmt);
    sqlite3_prepare_v2((*se)->db, "UPDATE teams SET user_uuids = ? WHERE uuid = ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, tmp, -1, SQLITE_STATIC);
    sqlite3_bind_text((*se)->stmt, 2, (*se)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    sqlite3_finalize((*se)->stmt);
    server_event_user_unsubscribed((*se)->command[1], cli->uuid_text);
}

int unsubscribe_function    (server **se, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*se)->command, 2, sd))
        return 0;
    char to_send[1024] = {0};
    if (!check_if_uuid_exists((*se)->command[1], "teams", (*se)->db)) {
        strcpy(to_send, CODE_500); strcat(to_send, curr_cli->team);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    if (!user_already_subscribed(se, curr_cli,
    (*se)->command[1], (*se)->db)) {
        strcpy(to_send, CODE_231); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    unsubscribe_sql_commands(se, cli_list, curr_cli, sd);
    return 0;
}
