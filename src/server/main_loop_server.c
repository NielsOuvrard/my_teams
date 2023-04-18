/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** main
*/

#include "my_server.h"
#include <signal.h>

static int keepRunning = 1;

void int_handler(int dummy)
{
    keepRunning = 0;
}

void server_loop_keep_running(server **serv, client **clients)
{
    fd_set copy_fds = (*serv)->readfds;
    int ret = select((*serv)->max_fds + 1, &copy_fds, NULL, NULL, NULL);
    if (ret == -1) {
        if (errno != EINTR) {
            perror("select");
            exit(EXIT_FAILURE);
        }
    } else {
        handle_new_connection(serv, clients, copy_fds);
        client_communication(serv, clients, copy_fds);
    }
}

void server_loop(server **serv, client **clients)
{
    struct sigaction sa;
    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    while (keepRunning)
        server_loop_keep_running(serv, clients);
    char *err_msg;
    if (sqlite3_exec((*serv)->db, "UPDATE users SET connected = 0",
    0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    for (int i = 0; i < MAX_CLIENTS; i++)
        if ((*clients)[i].is_logged)
            send((*clients)[i].socket, CODE_202, strlen(CODE_202) + 1, 0);
}
