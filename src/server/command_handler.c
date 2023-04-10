/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_handler
*/

#include "my_server.h"

bool check_valid_command_args(server **serv,
client *current_client, int sd)
{
    int count = 0, nbr_args = 0;
    for (int i = 0; (*serv)->command[i] != NULL; i++, nbr_args++);
    if (nbr_args <= 1)
        return true;
    for (int i = 1; (*serv)->command[i] != NULL; i++) {
        char *tmp = strdup((*serv)->command[i]);
        tmp = strchr(tmp, '\"');

        while (tmp != NULL) {
            count++;
            tmp = strchr(tmp + 1, '\"');
        }
    }
    if (count % 2 != 0 || ((count / 2) + 1) != nbr_args || count == 0) {
        send(sd, CODE_590, strlen(CODE_590) + 1, 0);
        return false;
    }
    return true;
}

void remove_quotes(server **serv)
{
    for (int i = 1; (*serv)->command[i] != NULL; i++) {
        char *tmp = strdup((*serv)->command[i]);
        tmp = strchr(tmp, '\"');
        if (tmp != NULL) {
            (*serv)->command[i] = &(*serv)->command[i][1];
            (*serv)->command[i][strlen((*serv)->command[i]) - 1] = '\0';
        }
    }
}

void command_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    if (!(*serv)->command || !(*serv)->command[0])
        return;
    remove_quotes(serv);
    for (int i = 0; i < NB_COMMANDS; i++) {
        if (strcmp((*serv)->fct[i].name, (*serv)->command[0]) == 0) {
            (*serv)->fct[i].fct(serv, cli_list, current_client, sd);
            return;
        }
    }
    send(sd, CODE_590, strlen(CODE_590) + 1, 0);
}

char **get_command(int sd)
{
    char buffer[1024] = {0};
    recv(sd, buffer, 1024, 0);
    char **command = my_str_to_word_array(buffer);
    return command;
}

void error_sql(server *serv, char *error)
{
    fprintf(stderr, error, sqlite3_errmsg(serv->users_db));
    exit (84);
}

void change_status_user (server **serv, const char *uuid_text, int status)
{
    char request[1024], *err_msg;
    sprintf(request, "UPDATE users SET connected = %d WHERE uuid = '%s'",
    status, uuid_text);
    int rc = sqlite3_exec((*serv)->users_db, request, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}
