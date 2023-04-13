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
                            client *curr_cli, int sd)
{
    // curr_cli->team = NULL;
    // curr_cli->channel = NULL;
    // curr_cli->thread = NULL;
    // char *team = (*serv)->command[1];
    // char *channel = (*serv)->command[2];
    // char *thread = (*serv)->command[3];
    // if (team)
    //     curr_cli->team = get_team_by_uuid(serv, team);
    // if (channel)
    //     curr_cli->channel = get_channel_by_uuid(serv, team, channel);
    // if (thread)
    //     curr_cli->thread = get_thread_by_uuid(serv, team, channel, thread);

    char to_send[1024];
    if (user_not_connected(curr_cli))
        return 0;
    if (args_check((*serv)->command, 1, sd)) {
        curr_cli->context = TEAM;
        return 0;
    }
    if (args_check((*serv)->command, 2, sd)) {
        strcpy(to_send, CODE_500);
        strcat(to_send, (*serv)->command[1]); strcat(to_send, "\n");
        if (!check_if_uuid_exists((*serv)->command[1], "teams",
        (*serv)->db)) {
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else {
            curr_cli->context = CHANNEL;
            curr_cli->team = (*serv)->command[1];
        }
    } else if (args_check((*serv)->command, 3, sd)) {
        if (!check_if_uuid_exists((*serv)->command[1], "teams",
        (*serv)->db)) {
            strcpy(to_send, CODE_500);
            strcat(to_send, (*serv)->command[2]); strcat(to_send, "\n");
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else if (!check_if_uuid_exists((*serv)->command[2], "channels", (*serv)->db)) {
            strcpy(to_send, CODE_501);
            strcat(to_send, (*serv)->command[2]); strcat(to_send, "\n");
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else {
            curr_cli->context = THREAD;
            curr_cli->team = (*serv)->command[1];
            curr_cli->channel = (*serv)->command[2];
        }
    } else {
        send(sd, CODE_590, strlen(CODE_590) + 1, 0);
    }
    return 0;
}
