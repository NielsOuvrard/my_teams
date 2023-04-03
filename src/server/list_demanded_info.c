/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** preload_users
*/

#include "my_server.h"

int client_is_logged(client **clients, char *uuid_text)
{
    for (int i = 0; i != MAX_CLIENTS; i++)
        if ((*clients)[i].socket != -1 &&
        strcmp((*clients)[i].uuid_text, uuid_text) == 0)
            return (*clients)[i].is_logged;
    return 0;
}

char **get_infos(server *serv, char *file_path)
{
    char *line = NULL;
    size_t len = 0;
    FILE *fd = fopen(file_path, "r");
    char **infos = NULL;
    int i = 0;
    while (getline(&line, &len, fd) != -1) {
        char *tmp = strdup(line);
        infos = realloc(infos, sizeof(char *) * (i + 1));
        infos[i] = tmp;
        i++;
    }
    infos = realloc(infos, sizeof(char *) * (i + 1));
    infos[i] = NULL;
    fclose(fd);
    return infos;
}
