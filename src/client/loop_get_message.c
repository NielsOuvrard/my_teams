/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

char *get_message(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    if (getline(&line, &len, stdin) == -1)
        return NULL;
    return line;
}

char *loop_get_message(void)
{
    char *message;
    if (!(message = get_message()))
        return NULL;
    if (message[0] == '\n')
        return loop_get_message();
    return message;
}
