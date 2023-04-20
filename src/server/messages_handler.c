/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** messages_handler
*/

#include "my_server.h"

int send_function(server **serv, client **cli_list,
client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 3, sd)
    || !check_if_user_exist(serv, sd))
        return 0;
    char *infos[5];
    int receiver = find_message_receiver(serv, cli_list);
    infos[0] = CODE_205;
    infos[1] = curr_cli->uuid_text;
    infos[2] = (*serv)->command[2];
    infos[3] = NULL;
    server_event_private_message_sended(curr_cli->uuid_text,
    (*serv)->command[1], (*serv)->command[2]);
    send(sd, CODE_221, strlen(CODE_205) + 1, 0);
    save_message_in_db(serv, curr_cli);
    send_info_client(infos, receiver);
    return 0;
}

int prepare_messages_historic(server **serv, client *curr_cli,
char to_send[4096], int sd)
{
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        char tmp[1024];
        sprintf(tmp, "%s\n%s\n%s",
        sqlite3_column_text((*serv)->stmt, 1),
        sqlite3_column_text((*serv)->stmt, 3),
        sqlite3_column_text((*serv)->stmt, 4));
        strcat(to_send, tmp);
    }
    int result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to finalize statement: %s\n",
        sqlite3_errmsg((*serv)->db));
    send(sd, to_send, strlen(to_send) + 1, 0);
}

int messages_handler(server **serv, client **cli_list,
client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 2, sd)
    || !check_if_user_exist(serv, sd))
        return 0;
    char request[1024], to_send[4096];
    strcpy(to_send, CODE_206);
    sprintf(request, "SELECT * FROM messages WHERE (sender = '%s'\
    AND receiver = '%s')  OR (sender = '%s' AND receiver = '%s');",
    (*serv)->command[1], curr_cli->uuid_text, curr_cli->uuid_text,
    (*serv)->command[1]);
    int result = sqlite3_prepare_v2((*serv)->db, request,
    -1, &(*serv)->stmt, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize((*serv)->stmt);
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*serv)->db));
    }
    prepare_messages_historic(serv, curr_cli, to_send, sd);
    return 0;
}
