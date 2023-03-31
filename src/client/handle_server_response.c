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

// void handle_server_response(client *cli)
// {
//     char server_reply[2000];
//     // whie protocol received == 250
//     {
//         if (recv(cli->sock, server_reply, 2000, 0) < 0) {
//             puts("recv failed");
//             return;
//             // check func to exec
//             // 600 cleint
//         }
//         char **array = my_str_parse(server_reply, " \n");
//         if (strcmp(array[0], "##UUID") == 0) {
//             char *infos[2];
//             infos[0] = array[1];
//             infos[1] = array[3];
//             exec_function_2(cli, infos, "client_event_logged_in");
//             printf("You are now logged in as %s\n", array[3]);
//         }
//         // array[1] = UUID
//         // array[3] = name
//         // array[5] = description / status
//         // print_map(array);
//         free_my_array(array);
//     }
// }
void handle_server_response(client *cli)
{
    char server_reply[2000];
    {
        if (recv(cli->sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            return;
        }
        char **array = my_str_parse(server_reply, " \n");
        if (strcmp(array[0], "##UUID") == 0) {
            char *infos[2];
            infos[0] = array[1];
            infos[1] = array[3];
            exec_function_2(cli, infos, "client_event_logged_in");
            printf("You are now logged in as %s\n", array[3]);
        }
        free_my_array(array);
    }
}
