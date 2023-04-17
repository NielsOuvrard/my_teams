/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** main
*/

#include "my_server.h"

void server_loop(server **serv, client **clients);

int load_all_users(server *serv)
{
    int result = sqlite3_prepare_v2(serv->db, "SELECT * FROM users;",
    -1, &serv->stmt, NULL);
    if (result != SQLITE_OK) {
        sqlite3_finalize(serv->stmt);
        return fprintf(stderr, "Falha ao preparar a declaração: %s\n",
        sqlite3_errmsg(serv->db));
    }
    while (sqlite3_step(serv->stmt) == SQLITE_ROW) {
        server_event_user_loaded(sqlite3_column_text(serv->stmt, 1),
        sqlite3_column_text(serv->stmt, 2));
    }
    result = sqlite3_finalize(serv->stmt);
    if (result != SQLITE_OK)
        return fprintf(stderr, "Falha ao finalizar a instrução: %s\n",
        sqlite3_errmsg(serv->db));
}

// function who free all the memory
int free_all(server *serv, client *clients, int return_value)
{
    shutdown(serv->socket_fd, SHUT_RDWR);
    free(serv->fct);
    for (int i = 0; i != MAX_CLIENTS; i++) {
        free(clients[i].uuid_text);
        if (clients[i].username) {
            free(clients[i].username);
        }
    }
    free(clients);
    if (return_value == 0) {
        int ret = sqlite3_close(serv->db);
        if (ret != SQLITE_OK)
            printf("Error: sqlite3_close() = %d\n", ret);
    }
    free(serv);
    return return_value;
}

int my_teams(int port)
{
    server *serv = construct_struct(port);
    if (!serv) {
        printf("Error: select() failed\n");
        return 84;
    }
    client *clients = malloc(sizeof(client) * (MAX_CLIENTS + 1));
    initialize_client(&clients);
    if (initialize_server(serv->socket_fd, serv->address) == -1)
        return free_all(serv, clients, 84);
    if (initialize_db(&serv) == -1)
        return free_all(serv, clients, 84);
    load_all_users(serv);
    server_loop(&serv, &clients);
    return free_all(serv, clients, 0);
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
    return my_teams(atoi(av[1]));
}
