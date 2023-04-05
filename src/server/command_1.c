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
    login_handler(serv, current_client, sd);
    return 0;
}

int logout_function         (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    logout_handler(serv, current_client, sd);
    return 0;
}

// code 203
// uuid
// username
// status
int users_function          (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 1, sd))
        return 0;
    int result = sqlite3_prepare_v2((*serv)->users_db, "SELECT * FROM users WHERE username = ?;", -1, &(*serv)->stmt, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg((*serv)->users_db));
        return 1;
    }
    char to_send[4096];
    strcpy(to_send, CODE_203);
    strcat(to_send, "\n");
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        sprintf(to_send, "UUID: %d, Username: %s, status: %s\n",
        sqlite3_column_text((*serv)->stmt, 1),
        sqlite3_column_text((*serv)->stmt, 2),
        sqlite3_column_int((*serv)->stmt, 3));
    }
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg((*serv)->users_db));
        return 1;
    }
    send(sd, to_send, strlen(to_send), 0);
    return 0;
}

int user_function           (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 2, sd))
        return 0;
    char filepath[1024];
    sprintf(filepath, "%s%s", "data/users/", (*serv)->command[1]);
    char *username = filepath_to_str(filepath);
    char *infos[5];
    infos[0] = CODE_204;
    infos[1] = (*serv)->command[1];
    infos[2] = username;
    infos[3] = client_is_logged(cli_list, (*serv)->command[1]) ? "1" : "0";
    infos[4] = NULL;
    send_info_client(infos, sd);
    return 0;
}

int send_function           (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    char **usr, path[1024], *filename = NULL;
    if (user_not_connected(curr_cli) ||!args_check((*serv)->command, 3, sd))
        return 0;
    char *infos[5];
    sprintf(path, "%s%s", "data/users/", (*serv)->command[1]);
    if (!check_file_exist(path)) {
        infos[0] = CODE_503;
        infos[1] = (*serv)->command[1];
        infos[2] = NULL;
    } else {
        infos[0] = CODE_205;
        infos[1] = (*serv)->command[1];
        infos[2] = filename;
        infos[3] = NULL;
        server_event_private_message_sended(curr_cli->uuid_text, (*serv)->command[1], (*serv)->command[2]);
    }
    send_info_client(infos, sd);
    return 0;
}
