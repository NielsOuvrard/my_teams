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
        return true;
    }
    sqlite3_finalize((*se)->stmt);
    return false;
}

char *get_user_info(server **se, client *cli, char *user_uuid)
{
    sqlite3_prepare_v2((*se)->db, "SELECT * FROM users WHERE uuid = ?;",
    -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, user_uuid, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_info = malloc(sizeof(char) * 1024);
    sprintf(user_info, "%s\n%s\n%d\n",
    (char *)sqlite3_column_text((*se)->stmt, 1),
    (char *)sqlite3_column_text((*se)->stmt, 2),
    sqlite3_column_int((*se)->stmt, 3));
    sqlite3_finalize((*se)->stmt);
    return user_info;
}

int subscribed_function     (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 2, sd))
        return 0;
    if (!check_if_uuid_exists((*serv)->command[1], "teams", (*serv)->db)) {
        send(sd, CODE_501, strlen(CODE_501), 0); return 0;
    }
    sqlite3_prepare_v2((*serv)->db,
    "SELECT user_uuids FROM teams WHERE uuid = ?;", -1, &(*serv)->stmt, NULL);
    sqlite3_bind_text((*serv)->stmt, 1,
    (*serv)->command[1], -1, SQLITE_STATIC);
    sqlite3_step((*serv)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*serv)->stmt, 0), *tmp;
    char **array = my_str_parse(user_uuids, ","), list[4096] = {0};
    strcpy(list, CODE_208);
    for (int i = 0; array[i] != NULL; i++){
        if (array[i]){
            strcat(list, get_user_info(serv, curr_cli, array[i]));
        }
    }
    send(sd, list, strlen(list), 0);
}

int use_function            (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli))
        return 0;
    clean_use_client(curr_cli);
    if (args_check((*serv)->command, 2, sd))
        curr_cli->team = strdup((*serv)->command[1]);
    if (args_check((*serv)->command, 3, sd)) {
        curr_cli->team = strdup((*serv)->command[1]);
        curr_cli->channel = strdup((*serv)->command[2]);
    }
    if (args_check((*serv)->command, 4, sd)) {
        curr_cli->team = strdup((*serv)->command[1]);
        curr_cli->channel = strdup((*serv)->command[2]);
        curr_cli->thread = strdup((*serv)->command[3]);
    }
    return 0;
}
