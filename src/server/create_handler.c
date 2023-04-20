/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** context_handler
*/

#include "my_server.h"

void send_message_to_every_one(server **se, client **cli_list,
client *cli, char *message);

char *send_code_and_value(char *code, char *value, int sd);

int handler_create_team (server **se, client **cli_list, client *cli, int sd)
{
    if (check_if_name_exists((*se)->command[1], "teams", (*se)->db)) {
        send(sd, CODE_505, strlen(CODE_505) + 1, 0);
    } else {
        char *to_send = create_team(se, cli_list, cli, sd);
        send_message_to_every_one(se, cli_list, cli, to_send);
        free(to_send);
    }
    return 0;
}

int handler_create_channel (server **se, client **cli_list, client *cli, int sd)
{
    if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
        send_code_and_value(CODE_500, cli->team, sd);
        return 0;
    }
    if (check_if_name_exists_where((*se)->command[1], cli->team,
    "SELECT name FROM channels WHERE name = ? AND team = ?;",
    (*se)->db)) {
        send(sd, CODE_505, strlen(CODE_505) + 1, 0);
    } else {
        char *to_send = create_channel(se, cli_list, cli, sd);
        send_message_to_every_one(se, cli_list, cli, to_send);
        free(to_send);
    }
    return 0;
}

int handler_create_thread (server **se, client **cli_list, client *cli, int sd)
{
    if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
        send_code_and_value(CODE_500, cli->team, sd);
        return 0;
    }
    if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db)) {
        send_code_and_value(CODE_501, cli->channel, sd);
        return 0;
    }
    if (check_if_name_exists_where((*se)->command[1], cli->channel,
    "SELECT title FROM threads WHERE title = ? AND channel = ?;",
    (*se)->db)) {
        send(sd, CODE_505, strlen(CODE_505) + 1, 0);
    } else {
        char *to_send = create_thread(se, cli_list, cli, sd);
        send_message_to_every_one(se, cli_list, cli, to_send);
        free(to_send);
    }
    return 0;
}

int handler_create_reply (server **se, client **cli_list, client *cli, int sd)
{
    if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
        send_code_and_value(CODE_500, cli->team, sd);
        return 0;
    }
    if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db)) {
        send_code_and_value(CODE_501, cli->channel, sd);
        return 0;
    }
    if (!check_if_uuid_exists(cli->thread, "threads", (*se)->db)) {
        send_code_and_value(CODE_502, cli->thread, sd);
        return 0;
    }
    char *to_send = create_reply(se, cli_list, cli, sd);
    send_message_to_every_one(se, cli_list, cli, to_send);
    free(to_send);
    return 0;
}

int create_handler(server **se, client **cli_list, client *cli, int sd)
{
    if (user_not_connected(cli))
        return 0;
    if (!cli->team)
        return handler_create_team(se, cli_list, cli, sd);
    if (cli->team && !cli->channel &&
    !user_not_subscribed(se, cli, cli->team, (*se)->db))
        return handler_create_channel(se, cli_list, cli, sd);
    if (cli->team && cli->channel && !cli->thread &&
    !user_not_subscribed(se, cli, cli->team, (*se)->db))
        return handler_create_thread(se, cli_list, cli, sd);
    if (cli->team && cli->channel && cli->thread)
        return handler_create_reply(se, cli_list, cli, sd);
    return 0;
}
