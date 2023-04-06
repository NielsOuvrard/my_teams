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
        char msg[100];
        sprintf(msg, "%s\n", CODE_590);
        send(sd, msg, strlen(msg), 0);
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

int command_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    (*serv)->simple_command = strcat((*serv)->simple_command, get_command(sd));
    if (!(*serv)->simple_command || !(*serv)->simple_command[0]
    || (*serv)->simple_command[strlen((*serv)->simple_command) - 1] != '\n')
        return 0;
    (*serv)->command = my_str_to_word_array((*serv)->simple_command);
    char msg[100];
    sprintf(msg, "%s\n", CODE_590);
    if (!check_valid_command_args(serv, current_client, sd)) {
        send(sd, msg, strlen(msg), 0);
        return 1;
    }
    remove_quotes(serv);
    for (int i = 0; i < NB_COMMANDS; i++) {
        if (strcmp((*serv)->fct[i].name, (*serv)->command[0]) == 0) {
            (*serv)->fct[i].fct(serv, cli_list, current_client, sd);
            return 1;
        }
    }
    send(sd, msg, strlen(msg), 0);
    return 1;
}

char *get_command(int sd)
{
    char *buffer = malloc(sizeof(char) * 1024);
    memset(buffer, 0, 1024);
    recv(sd, buffer, 1024, 0);
    return buffer;
}

void error_sql(server *serv, char *error)
{
    fprintf(stderr, error, sqlite3_errmsg(serv->users_db));
    exit (84);
}

void change_status_user (server **serv, const char *uuid_text, int status)
{
    char request[1024];
    sprintf(request, "UPDATE users SET connected = %d WHERE uuid = %s",
    status, uuid_text);
    sqlite3_prepare_v2((*serv)->users_db, request, -1, &(*serv)->stmt, NULL);
}
