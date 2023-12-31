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
    if (cli->is_connected == false) {
        cli->is_connected = true;
        cli->uuid = strdup(array[1]);
        cli->name = strdup(array[2]);
    }
    return client_event_logged_in(array[1], array[2]);
}

// 1 = client_event_logged_out, type 3
// 17 = client_error_unauthorized, type 0
//fix core dump when quitting server with crtl + c
int logout_function         (client *cli, char **array)
{
    if (!array[1] || (strcmp(array[1], cli->uuid) == 0 &&
    strcmp(array[2], cli->name) == 0)) {
        client_event_logged_out(cli->uuid, cli->name);
        free(cli->uuid);
        free(cli->name);
        return -1;
    } else {
        client_event_logged_out(array[1], array[2]);
        return 0;
    }
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
        client_print_users(uuid, name, atoi(status));
    }
    return 0;
}

// 19 = client_print_user
// client_error_unknown_user
int user_function           (client *cli, char **array)
{
    return client_print_user(array[1], array[2], atoi(array[3]));
}

int send_function           (client *cli, char **array)
{
    return client_event_private_message_received(array[1], array[2]);
}
