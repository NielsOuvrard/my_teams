/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** send_infos_client
*/

#include "my.h"

void send_info(char **infos, int sd)
{
    char *str = malloc(sizeof(char) * 1024);
    for (int i = 0; infos[i] != NULL; i++) {
        str = strcat(str, infos[i]);
    }
    send(sd, str, strlen(str), 0);
    free(str);
}
