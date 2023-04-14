/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** context_handler
*/

#include "my_server.h"

void send_message_to_every_one(server **se, client **cli_list,
client *cli, char *message)
{
    sqlite3_prepare_v2((*se)->db, "SELECT user_uuids FROM teams WHERE uuid = ?;", -1, &(*se)->stmt, NULL);
    sqlite3_bind_text((*se)->stmt, 1, cli->team, -1, SQLITE_STATIC);
    sqlite3_step((*se)->stmt);
    char *user_uuids = (char *)sqlite3_column_text((*se)->stmt, 0);
    printf("user_uuids: %s\n", user_uuids);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (cli_list[i]->socket != -1 && strstr(user_uuids, cli_list[i]->uuid_text)) {
            printf("Sending message to %s\n", cli_list[i]->username);
            send(cli_list[i]->socket, message, strlen(message) + 1, 0);
        }
    }
}

char *create_handler_3(server **se, client **cli_list, client *cli, int sd)
{
    char to_send[1024];
    memset(to_send, 0, 1024);
    if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
        strcpy(to_send, CODE_500); strcat(to_send, cli->team);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    } else if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db)) {
        strcpy(to_send, CODE_501); strcat(to_send, cli->channel);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    if (!check_if_uuid_exists(cli->thread, "threads", (*se)->db)) {
        strcpy(to_send, CODE_502); strcat(to_send, cli->thread);
        strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
        return 0;
    }
    // to_send = why ?
    create_reply(se, cli_list, cli, sd);
}

char *create_handler_2(server **se, client **cli_list, client *cli, int sd)
{
    char to_send[1024] = {0};
    if (user_not_subscribed(se, cli, cli->team, (*se)->db))
        return 0;
    if (cli->team && cli->channel && !cli->thread) {
        if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
            strcpy(to_send, CODE_500); strcat(to_send, cli->team);
            strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
            return 0;
        } else if (!check_if_uuid_exists(cli->channel, "channels", (*se)->db)) {
            strcpy(to_send, CODE_501); strcat(to_send, cli->channel);
            strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
            return 0;
        }
        if (check_if_name_exists((*se)->command[1], "threads", (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0); return 0;
        } else {
            return create_thread(se, cli_list, cli, sd);
        }
    } else if (cli->team && cli->channel && cli->thread) {
        return create_handler_3(se, cli_list, cli, sd);
    }
    return 0;
}

int create_handler(server **se, client **cli_list, client *cli, int sd)
{
    if (user_not_connected(cli))
        return 0;
    char *to_send = malloc(sizeof(char) * 1024);
    if (!cli->team) {
        if (check_if_name_exists((*se)->command[1], "teams", (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0); return 0;
        } else {
            create_team(se, cli_list, cli, sd);
            return 0;
        }
    } else if (cli->team && !cli->channel && !user_not_subscribed(se, cli, cli->team, (*se)->db)) {
        if (!check_if_uuid_exists(cli->team, "teams", (*se)->db)) {
            strcpy(to_send, CODE_500); strcat(to_send, cli->team);
            strcat(to_send, "\n"); send(sd, to_send, strlen(to_send) + 1, 0);
            return 0;
        }
        if (check_if_name_exists((*se)->command[1], "channels", (*se)->db)) {
            send(sd, CODE_505, strlen(CODE_505) + 1, 0); return 0;
        } else {
            free(to_send);
            to_send = create_channel(se, cli_list, cli, sd);
        }
    } else
        to_send = create_handler_2(se, cli_list, cli, sd);
    send_message_to_every_one(se, cli_list, cli, to_send);
    free(to_send);
    return 0;
}
