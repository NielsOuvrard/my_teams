/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

bool check_valid_command_args(char *message)
{
    int count = 0, nbr_args = 0;
    char **array = my_str_parse(message, " ");
    for (int i = 0; array[i] != NULL; i++, nbr_args++);
    if (nbr_args <= 1)
        return true;
    for (int i = 1; array[i] != NULL; i++) {
        char *tmp = strdup(array[i]);
        tmp = strchr(tmp, '\"');
        while (tmp != NULL) {
            count++;
            tmp = strchr(tmp + 1, '\"');
        }
    }
    if (count % 2 != 0 || ((count / 2) + 1) != nbr_args || count == 0)
        return false;
    return true;
}

char *get_message(void)
{
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stdin) == -1)
        return NULL;
    return line;
}

// invalid read of size 1 line 44
char *loop_get_message(char *message)
{
    if (message == NULL)
        message = malloc(sizeof(char) * 1024);
    if (!(message = strcat(message, get_message())))
        return NULL;
    if (message[0] == '\n')
        return loop_get_message(message);
    if (message[strlen(message) - 1] != '\n' ||
    check_valid_command_args(message) == false)
        return loop_get_message(message);
    return message;
}
