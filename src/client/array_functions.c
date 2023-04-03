/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

// client_event_logged_in
// client_event_logged_out
// client_event_private_message_received
// client_event_thread_reply_received
// client_event_team_created
// client_event_channel_created
// client_event_thread_created
// client_print_users
// client_print_teams
// client_team_print_channels
// client_channel_print_threads
// client_thread_print_replies
// client_private_message_print_messages
// client_error_unknown_team
// client_error_unknown_channel
// client_error_unknown_thread
// client_error_unknown_user
// client_error_unauthorized
// client_error_already_exist
// client_print_user
// client_print_team
// client_print_channel
// client_print_thread
// client_print_team_created
// client_print_channel_created
// client_print_thread_created
// client_print_reply_created
// client_print_subscribed
// client_print_unsubscribed
fct_lib_t *load_library_data (client cli)
{
    char *funct_name[NB_CLI_FUNCT] = { LIST_CLI_FUNC };
    int nb_args[NB_CLI_FUNCT] = { LIST_TYPE_FUNC };
    fct_lib_t *data_lib = malloc(sizeof(fct_lib_t) * NB_CLI_FUNCT);
    for (int i = 0; i < NB_CLI_FUNCT; i++) {
        data_lib[i].name = funct_name[i];
        data_lib[i].type = nb_args[i];
        data_lib[i].fct = load_library_function(cli.lib, funct_name[i]);
    }
    return data_lib;
}

fct_client_t *array_struct(void)
{
    char *commandes[NB_COMMANDS] = { LIST_COMMANDS };
    char *code[NB_COMMANDS] = { LIST_CODE };
    command_func fptr[NB_COMMANDS] = { LIST_FUNC };
    fct_client_t *fct = malloc(sizeof(fct_client_t) * NB_COMMANDS);
    for (int i = 0; i < NB_COMMANDS; i++) {
        fct[i].name = commandes[i];
        fct[i].fct = fptr[i];
        fct[i].code = code[i];
    }
    return fct;
}
