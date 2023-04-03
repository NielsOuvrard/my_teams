/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

// 0 = client_event_logged_in
int login_function          (client *cli, char **array)
{
    cli->is_connected = 1;
    cli->uuid = strdup(array[1]);
    cli->name = strdup(array[2]);
    fct_2 fonction = cli->data_lib[0].fct;
    return fonction(array[1], array[2]);
}

// 1 = client_event_logged_out, type 3
// 17 = client_error_unauthorized, type 0
int logout_function         (client *cli, char **array)
{
    if (cli->is_connected == 1) {
        cli->is_connected = 0;
        free(cli->uuid);
        free(cli->name);
    }
    fct_2 fonction = cli->data_lib[1].fct;
    return fonction(array[1], array[2]);
}

// 7 = client_print_users
// user status
int users_function          (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 3) {
        if (array[i + 1] == NULL || array[i + 2] == NULL)
            return 0;
        char *uuid = array[i];
        char *name = array[i + 1];
        char *status = array[i + 2];
        fct_8 fonction = cli->data_lib[7].fct;
        fonction(uuid, name, atoi(status));
    }
    return 0;
}

// 19 = client_print_user
// client_error_unknown_user
int user_function           (client *cli, char **array)
{
    fct_8 fonction = cli->data_lib[19].fct;
    return fonction(array[1], array[2], atoi(array[3]));
}

int send_function           (client *cli, char **array)
{
    return 0;
}
