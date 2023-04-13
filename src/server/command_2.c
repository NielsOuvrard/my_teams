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

int use_function            (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
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
        (*serv)->teams_db)) {
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else {
            curr_cli->context = CHANNEL;
            curr_cli->team_uuid = (*serv)->command[1];
        }
    } else if (args_check((*serv)->command, 3, sd)) {
        if (!check_if_uuid_exists((*serv)->command[1], "teams",
        (*serv)->teams_db)) {
            strcpy(to_send, CODE_500);
            strcat(to_send, (*serv)->command[2]); strcat(to_send, "\n");
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else if (!check_if_uuid_exists((*serv)->command[2], "channels", (*serv)->channels_db)) {
            strcpy(to_send, CODE_501);
            strcat(to_send, (*serv)->command[2]); strcat(to_send, "\n");
            send(sd, to_send, strlen(to_send) + 1, 0);
        } else {
            curr_cli->context = THREAD;
            curr_cli->team_uuid = (*serv)->command[1];
            curr_cli->channel_uuid = (*serv)->command[2];
        }
    } else {
        send(sd, CODE_590, strlen(CODE_590) + 1, 0);
    }
    return 0;
}
