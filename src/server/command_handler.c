/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_handler
*/

#include "my.h"

void command_handler(server **serv, client **cli_list,
client *current_client, int sd)
{
    if (strcmp((*serv)->command[0], "/login") == 0) {
        login_handler(serv, current_client, sd);
        return;
    }
    if (strcmp((*serv)->command[0], "/logout") == 0) {
        logout_handler(serv, current_client, sd);
        return;
    }
    if (strcmp((*serv)->command[0], "/users") == 0) {
        users_list_handler(serv, cli_list, current_client, sd);
        return;
    }
    send(sd, "590 Invalid command.\n", 21, 0);
}

char **get_command(int sd)
{
    char buffer[1024] = {0};
    recv(sd, buffer, 1024, 0);
    char **command = my_str_to_word_array(buffer);
    return command;
}
