/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int messages_function       (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    messages_handler(serv, cli_list, curr_cli, sd);
    return 0;
}

int subscribe_function      (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int subscribed_function     (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int unsubscribe_function    (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

// [“team_uuid”] ? [“channel_uuid”] ? [“thread_uuid”]
// don't forget to send :
// client_error_unknown_team
// client_error_unknown_channel
// client_error_unknown_thread
// client_error_unknown_user
int use_function            (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    current_client->team = NULL;
    current_client->channel = NULL;
    current_client->thread = NULL;
    char *team = (*serv)->command[1];
    char *channel = (*serv)->command[2];
    char *thread = (*serv)->command[3];
    if (team)
        current_client->team = get_team_by_uuid(serv, team);
    if (channel)
        current_client->channel = get_channel_by_uuid(serv, team, channel);
    if (thread)
        current_client->thread = get_thread_by_uuid(serv, team, channel, thread);
    return 0;
}
