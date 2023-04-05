/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my_server.h"

// CODE_202 = "202 Logged out."
void logout_handler(server **serv, client *cur_cli, int sd)
{
    if (!args_check((*serv)->command, 1, sd) || user_not_connected(cur_cli))
        return;
    change_status_user(serv, cur_cli->uuid_text, 0);
    server_event_user_logged_out(cur_cli->uuid_text);
    char *to_send = malloc(sizeof(char) * 1024);
    sprintf(to_send, "%s\n%s\n%s", CODE_202, cur_cli->uuid_text,
    cur_cli->username);
    send(sd, to_send, strlen(to_send), 0);
    free(to_send);
    FD_CLR(sd, &(*serv)->readfds);
    close(sd);
    cur_cli->is_logged = false;
}

void execute_function_login(server **serv, client *current_client, int i)
{
    if (i == 0)
        server_event_user_created(current_client->uuid_text,
        current_client->username);
    else if (i == 1)
        server_event_user_logged_in(current_client->uuid_text);
}

// if the user exists
int user_exists(server **serv, client *cli, char *str)
{
    int result = sqlite3_prepare_v2((*serv)->users_db,
    "SELECT * FROM users WHERE username = ?;", -1, &(*serv)->stmt, NULL);
    if (result != SQLITE_OK) {
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*serv)->users_db));
    }
    sqlite3_bind_text((*serv)->stmt, 1,
    (*serv)->command[1], -1, SQLITE_STATIC);
    if (sqlite3_step((*serv)->stmt) == SQLITE_ROW) {
        cli->uuid_text = strdup(sqlite3_column_text((*serv)->stmt, 1));
        cli->username = strdup(sqlite3_column_text((*serv)->stmt, 2));
        sprintf(str, "%s\n%s\n%s\n", CODE_201, cli->uuid_text, cli->username);
    }
    change_status_user(serv, cli->uuid_text, 1);
}

// If the user doesn't exist
int user_doesnt_exist(server **serv, client *cli, char *str)
{
    cli->username = strdup((*serv)->command[1]);
    uuid_generate(cli->uuid);
    uuid_unparse(cli->uuid, cli->uuid_text);
    execute_function_login(serv, cli, 0);
    sprintf(str, "%s\n%s\n%s\n", CODE_201, cli->uuid_text, cli->username);
    int result = sqlite3_prepare_v2((*serv)->users_db,
    "INSERT INTO users (uuid, username, connected) VALUES (?, ?, ?);",
    -1, &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*serv)->users_db));
    sqlite3_bind_text((*serv)->stmt, 1, cli->uuid_text, -1, SQLITE_STATIC);
    sqlite3_bind_text((*serv)->stmt, 2, cli->username, -1, SQLITE_STATIC);
    sqlite3_bind_int((*serv)->stmt, 3, 1);
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        return fprintf(stderr, "Failed to insert data: %s\n",
        sqlite3_errmsg((*serv)->users_db));
}

int login_handler(server **se, client *cli, int sd)
{
    char str[1024];
    if (!args_check((*se)->command, 2, sd) || user_connected(cli))
        return 0;
    int result = sqlite3_prepare_v2((*se)->users_db,
    "SELECT COUNT(*) FROM users WHERE username = ?;", -1,
    &(*se)->stmt, NULL);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg((*se)->users_db));
    sqlite3_bind_text((*se)->stmt, 1, (*se)->command[1], -1, SQLITE_STATIC);
    if (sqlite3_step((*se)->stmt) == SQLITE_ROW)
        result = sqlite3_column_int((*se)->stmt, 0);
    if (result > 0)
        user_exists(se, cli, str);
    else
        user_doesnt_exist(se, cli, str);
    cli->is_logged = true;
    execute_function_login(se, cli, 1);
    send(sd, str, strlen(str), 0);
}
