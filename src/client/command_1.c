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
    fct_2 fonction = cli->data_lib[0].fct;
    return fonction(array[1], array[2]);
}

// 1 = client_event_logged_out
int logout_function         (client *cli, char **array)
{
    fct_2 fonction = cli->data_lib[1].fct;
    return fonction(array[1], array[2]);
}

// 7 = client_print_users
// user status
int users_function          (client *cli, char **array)
{
    fct_8 fonction = cli->data_lib[7].fct;
    return fonction(array[1], array[2], 0);
    return 0;
}

// 19 = client_print_user
// client_error_unknown_user
int user_function           (client *cli, char **array)
{
    fct_8 fonction = cli->data_lib[19].fct;
    return fonction(array[1], array[2], 0);
}

int send_function           (client *cli, char **array)
{
    return 0;
}
