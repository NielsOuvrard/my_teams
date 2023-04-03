/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** send_infos_client
*/

#include "my_server.h"

int nmb_char_in_array (char **array)
{
    int c = 0;
    for (int i = 0; array[i] != NULL; i++)
        c += strlen(array[i]);
    return c;
}

int array_len (char **array)
{
    int i = 0;
    for (; array[i] != NULL; i++);
    return i;
}

void send_info_client (char **infos, int sd)
{
    char *str = malloc(sizeof(char) *
    (nmb_char_in_array(infos) + array_len(infos) + 1));
    str[0] = '\0';
    for (int i = 0; infos[i] != NULL; i++) {
        strcat(str, infos[i]);
        strcat(str, "\n");
    }
    send(sd, str, strlen(str), 0);
    free(str);
}

void send_info(char **infos, int sd)
{
    char *str = malloc(sizeof(char) * 1024);
    str[0] = '\0';
    for (int i = 0; infos[i] != NULL; i++) {
        str = strcat(str, infos[i]);
    }
    send(sd, str, strlen(str), 0);
    free(str);
}

void free_my_array (char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
