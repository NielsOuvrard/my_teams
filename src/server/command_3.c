/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int create_function         (server **se, client **cli_list,
                            client *cli, int sd)
{
    return create_handler(se, cli_list, cli, sd);
}

char *list_function_2           (server **serv, client **cli_list,
                            client *cli, int sd)
{
    if (cli->team && cli->channel && cli->thread) {
        if (!check_if_uuid_exists(cli->team, "teams", (*serv)->db)) {
            send(sd, CODE_500, strlen(CODE_500), 0);
            return 0;
        }
        if (!check_if_uuid_exists(cli->channel, "channels", (*serv)->db)) {
            send(sd, CODE_501, strlen(CODE_501), 0);
            return 0;
        }
        if (!check_if_uuid_exists(cli->thread, "threads", (*serv)->db)) {
            send(sd, CODE_502, strlen(CODE_502), 0);
            return 0;
        }
        list_replies(serv, cli, sd);
    }
}

int list_function           (server **serv, client **cli_list,
                            client *cli, int sd)
{
    if (user_not_connected(cli) || !args_check((*serv)->command, 1, sd))
        return 0;
    if (!cli->team) list_team(serv, cli, sd);
    if (cli->team && !cli->channel) {
        if (!check_if_uuid_exists(cli->team, "teams", (*serv)->db)) {
            send(sd, CODE_500, strlen(CODE_500), 0); return 0;
        }
        list_channel(serv, cli, sd);
    }
    if (cli->team && cli->channel && !cli->thread) {
        if (!check_if_uuid_exists(cli->team, "teams", (*serv)->db)) {
            send(sd, CODE_500, strlen(CODE_500), 0);
            return 0;
        }
        if (!check_if_uuid_exists(cli->channel, "channels", (*serv)->db)) {
            send(sd, CODE_501, strlen(CODE_501), 0); return 0;
        }
        list_threads(serv, cli, sd);
    }
    list_function_2(serv, cli_list, cli, sd); return 0;
}

int info_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}

int help_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    send(sd, CODE_200, strlen(CODE_200), 0);
    return 0;
}
