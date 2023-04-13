/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int create_function         (server **serv, client **cli_list,
                            client *cli, int sd)
{
    if (!(*serv)->command[1])
        return send(sd, CODE_500, strlen(CODE_500) + 1, 0);
    if (!cli->team) {
        create_team(serv, cli_list, cli, sd);
        return 0;
    } else if (cli->team && !cli->channel) {
        create_channel(serv, cli_list, cli, sd);
        return 0;
    } // f*cking coding style
    if (cli->team && cli->channel && !cli->thread) {
        create_thread(serv, cli_list, cli, sd);
        return 0;
    } else if (cli->team && cli->channel && cli->thread) {
        create_reply(serv, cli_list, cli, sd);
        return 0;
    }
    return 0;
}

int list_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
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
