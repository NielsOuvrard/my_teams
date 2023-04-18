/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** list_handler
*/

#include "my_server.h"

int list_replies(server **serv, client *cli, int sd)
{
    char request[1024], *to_send = malloc(sizeof(char) * 4096);
    strcpy(request, "SELECT * FROM replies;");
    sqlite3_prepare_v2((*serv)->db, request, -1, &(*serv)->stmt, NULL);
    strcpy(to_send, CODE_215);
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 1));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 2));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 4));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 3));
        strcat(to_send, "\n");
    }
    sqlite3_finalize((*serv)->stmt);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int list_threads(server **serv, client *cli, int sd)
{
    char request[1024], *to_send = malloc(sizeof(char) * 4096);
    strcpy(request, "SELECT * FROM channels;");
    sqlite3_prepare_v2((*serv)->db, request, -1, &(*serv)->stmt, NULL);
    strcpy(to_send, CODE_215);
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 1));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 3));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 6));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 4));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 5));
        strcat(to_send, "\n");
    }
    sqlite3_finalize((*serv)->stmt);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int list_channel(server **serv, client *cli, int sd)
{
    char request[1024], *to_send = malloc(sizeof(char) * 4096);
    strcpy(request, "SELECT * FROM channels;");
    sqlite3_prepare_v2((*serv)->db, request, -1, &(*serv)->stmt, NULL);
    strcpy(to_send, CODE_215);
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 1));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 3));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 4));
        strcat(to_send, "\n");
    }
    sqlite3_finalize((*serv)->stmt);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}

int list_team(server **serv, client *cli, int sd)
{
    char request[1024], *to_send = malloc(sizeof(char) * 4096);
    strcpy(request, "SELECT * FROM teams;");
    sqlite3_prepare_v2((*serv)->db, request, -1, &(*serv)->stmt, NULL);
    strcpy(to_send, CODE_215);
    while (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 1));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 2));
        strcat(to_send, "\n");
        strcat(to_send, sqlite3_column_text((*serv)->stmt, 3));
        strcat(to_send, "\n");
    }
    sqlite3_finalize((*serv)->stmt);
    send(sd, to_send, strlen(to_send) + 1, 0);
    return 0;
}
