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
    if (getline(&line, &len, stdin) == -1) {
        free(line);
        return get_message();
    }
    return line;
}

char *loop_get_message(char *message)
{
    if (message == NULL) {
        message = malloc(sizeof(char) * 1024);
        memset(message, 0, 1024);
    }
    char *line = get_message();
    strcat(message, line);
    free(line);
    if (message[0] == '\n') {
        free(message);
        message = NULL;
        return loop_get_message(message);
    }
    if (message[strlen(message) - 1] != '\n') {
        free(message);
        message = NULL;
        return loop_get_message(message);
    }
    return message;
}
