/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** main
*/

#include "my_server.h"

void server_loop(server **serv, client **clients)
{
    while (1) {
        fd_set copy_fds = (*serv)->readfds;
        printf("here\n");
        if (select((*serv)->max_fds + 1, &copy_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        handle_new_connection(serv, clients, copy_fds);
        if (client_communication(serv, clients, copy_fds) == 1) {
            free((*serv)->simple_command);
            (*serv)->simple_command = malloc(sizeof(char) * 1024);
            memset((*serv)->simple_command, 0, 1024);
        }
    }
}

int load_all_users(server *serv)
{
    int result = sqlite3_prepare_v2(serv->users_db, "SELECT * FROM users;",
    -1, &serv->stmt, NULL);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to prepare statement: %s\n",
        sqlite3_errmsg(serv->users_db));
    while (sqlite3_step(serv->stmt) == SQLITE_ROW) {
        server_event_user_loaded(sqlite3_column_text(serv->stmt, 1),
        sqlite3_column_text(serv->stmt, 2));
    }
    result = sqlite3_finalize(serv->stmt);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Failed to finalize statement: %s\n",
        sqlite3_errmsg(serv->users_db));
}

void initialize_db(server **serv)
{
    int result;
    if (sqlite3_open("data/users.db", &(*serv)->users_db) != SQLITE_OK)
        error_sql(*serv, "Can't open database: %s\n");
    result = sqlite3_prepare_v2((*serv)->users_db, CREATE_DB, -1,
    &(*serv)->stmt, NULL);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to prepare statement: %s\n");
    result = sqlite3_step((*serv)->stmt);
    if (result != SQLITE_DONE)
        error_sql(*serv, "Failed to execute statement: %s\n");
    result = sqlite3_finalize((*serv)->stmt);
    if (result != SQLITE_OK)
        error_sql(*serv, "Failed to finalize statement: %s\n");
}

void my_teams(int port)
{
    server *serv = construct_struct(port);
    client *clients = malloc(sizeof(client) * (MAX_CLIENTS + 1));
    initialize_client(&clients);
    initialize_server(serv->socket_fd, serv->address);
    initialize_db(&serv);
    load_all_users(serv);
    server_loop(&serv, &clients);
    close(serv->socket_fd);
    shutdown(serv->socket_fd, SHUT_RDWR);
    free(serv);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n");
        printf("\tport is the port number on which the server");
        printf(" socloginket listens.\n");
        return 0;
    } else if (ac != 2) {
        printf("./myteams_server -help\n");
        return 84;
    }
    for (int i = 0; av[1][i] != '\0'; i++) {
        if (isdigit(av[1][i]) == 0) {
            return 84;
        }
    }
    my_teams(atoi(av[1]));
    return 0;
}
