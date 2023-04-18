/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int login_function          (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    if (login_handler(serv, current_client, sd) == 1)
        return 0;
    send_event_logged_in(serv, cli_list, current_client, sd);
    return 0;
}

int logout_function         (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    if (logout_handler(serv, current_client, sd) == 1)
        return 0;
    send_event_logged_out(serv, cli_list, current_client, sd);
    remove_client(current_client, sd);
    return 0;
}

void fill_to_send_users(char *to_send, server **serv)
{
    char tmp[1024];
    sprintf(tmp, "%s\n%s\n%d\n",
    sqlite3_column_text((*serv)->stmt, 1),
    sqlite3_column_text((*serv)->stmt, 2),
    sqlite3_column_int((*serv)->stmt, 3));
    strcat(to_send, tmp);
}

int users_function          (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 1, sd))
        return 0;
    int result = sqlite3_prepare_v2((*serv)->db,
    "SELECT * FROM users", -1, &(*serv)->stmt, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize((*serv)->stmt);
        return fprintf(stderr, "Falha ao preparar a declaração: %s\n",
        sqlite3_errmsg((*serv)->db));
    }
    char to_send[4096];
    strcpy(to_send, CODE_203);
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW)
        fill_to_send_users(to_send, serv);
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Falha ao finalizar a instrução: %s\n",
        sqlite3_errmsg((*serv)->db));
    return send(sd, to_send, strlen(to_send) + 1, 0);
}

int user_function           (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 2, sd)
    || !check_if_user_exist(serv, sd))
        return 0;
    char request[1024];
    sprintf(request, "SELECT * FROM users WHERE uuid = '%s';",
    (*serv)->command[1]);
    sqlite3_prepare_v2((*serv)->db, request, -1,
    &(*serv)->stmt, NULL);
    if (!sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        sqlite3_finalize((*serv)->stmt);
        return send_info_client((char *[]) { CODE_503 , NULL}, sd);
    }
    char *infos[5];
    infos[0] = CODE_204;
    infos[1] = (*serv)->command[1];
    infos[2] = strdup(sqlite3_column_text((*serv)->stmt, 2));
    infos[3] = ((sqlite3_column_int((*serv)->stmt, 3)) ? "1" : "0");
    infos[4] = NULL;
    sqlite3_finalize((*serv)->stmt);
    return send_info_client(infos, sd);
}
