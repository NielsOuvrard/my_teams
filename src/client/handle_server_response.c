/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

void free_my_array (char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int check_all_functions (client *cli, char **array)
{
    for (int i = 0; i < NB_COMMANDS; i++) {
        if (strncmp(array[0], cli->funct_client[i].name,
        strlen(cli->funct_client[i].name)) == 0) {
            return cli->funct_client[i].fct(cli, array);
        }
    }
}

// print_array(array);
void handle_server_response(client *cli)
{
    char server_reply[2000];
    if (recv(cli->sock, server_reply, 2000, 0) < 0) {
        puts("recv failed");
        return;
    }
    char **array = my_str_parse(server_reply, "\n");
    printf("Server reply :\n");
    check_all_functions(cli, array);
    free_my_array(array);
}
