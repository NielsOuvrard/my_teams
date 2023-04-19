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

char *create_handler_3(server **se, client **cli_list, client *cli, int sd)
{
    char *to_send = malloc(sizeof(char) * 1024);
    memset(to_send, 0, 1024);
    if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
        return send_code_and_value(CODE_500, cli->team, sd);
    } else if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db)) {
        return send_code_and_value(CODE_501, cli->channel, sd);
    }
    if (!check_if_uuid_exists(cli->thread, "threads", (*se)->db)) {
        return send_code_and_value(CODE_502, cli->thread, sd);
    }
    return create_reply(se, cli_list, cli, sd);
}

char *create_handler_2(server **se, client **cli_list, client *cli, int sd)
{
    char to_send[1024] = {0};
    if (user_not_subscribed(se, cli, cli->team, (*se)->db))
        return "error";
    if (cli->team && cli->channel && !cli->thread) {
        if (!check_if_uuid_exists(cli->team, "teams", (*se)->db))
            return send_code_and_value(CODE_500, cli->team, sd);
        if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db))
            return send_code_and_value(CODE_501, cli->channel, sd);
        if (check_if_name_exists_where((*se)->command[1], cli->channel,
        "SELECT title FROM threads WHERE title = ? AND channel = ?;",
        (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return "error";
        } else {
            return create_thread(se, cli_list, cli, sd);
        }
    } else if (cli->team && cli->channel && cli->thread) {
        return create_handler_3(se, cli_list, cli, sd);
    }
    return "error";
}

char *create_handler_first_cond(server **se, client **cli_list, client *cli,
int sd)
{
    if (!cli->team) {
        if (check_if_name_exists((*se)->command[1], "teams", (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return NULL;
        } else {
            return create_team(se, cli_list, cli, sd);
        }
    }
    return "next";
}

char *create_handler_second_cond(server **se, client **cli_list, client *cli,
int sd)
{
    if (cli->team && !cli->channel &&
    !user_not_subscribed(se, cli, cli->team, (*se)->db)) {
        if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
            send_code_and_value(CODE_500, cli->team, sd);
            return NULL;
        }
        if (check_if_name_exists_where((*se)->command[1], cli->team,
        "SELECT name FROM channels WHERE name = ? AND team = ?;",
        (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0);
            return NULL;
        } else {
            return create_channel(se, cli_list, cli, sd);
        }
    } else if (cli->team) {
        return create_handler_2(se, cli_list, cli, sd);
    }
    return "error";
}

int create_handler(server **se, client **cli_list, client *cli, int sd)
{
    if (user_not_connected(cli))
        return 0;
    char *to_send = create_handler_first_cond(se, cli_list, cli, sd);
    if (to_send == NULL)
        return 0;
    else if (strcmp(to_send, "next") == 0)
        to_send = create_handler_second_cond(se, cli_list, cli, sd);
    if (to_send == NULL)
        return 0;
    if (strcmp(to_send, "error") == 0)
        return 0;
    send_message_to_every_one(se, cli_list, cli, to_send);
    // free(to_send);
    return 0;
}
