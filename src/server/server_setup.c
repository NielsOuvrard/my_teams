/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** server_setup
*/

#include "my_server.h"

int initialize_server(int socket_fd, struct sockaddr_in address)
{
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket");
        return -1;
    }
    if (listen(socket_fd, MAX_CLIENTS) < 0) {
        perror("Failed to listen");
        return -1;
    }
    return 1;
}

fct_server_t *array_struct(void)
{
    char *commandes[NB_COMMANDS] = { COMMANDS_NAME };
    command_func fptr[NB_COMMANDS] = { COMMANDS_FCT };
    fct_server_t *fct = malloc(sizeof(fct_server_t) * (NB_COMMANDS + 1));
    for (int i = 0; i < NB_COMMANDS; i++) {
        fct[i].name = commandes[i];
        fct[i].fct = fptr[i];
    }
    return fct;
}

server *construct_struct(int port)
{
    server *serv = malloc(sizeof(server));
    serv->port = port;
    serv->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv->socket_fd == -1) {
        perror("socket");
        free(serv);
        return NULL;
    }
    serv->address.sin_family = AF_INET;
    serv->address.sin_addr.s_addr = INADDR_ANY;
    serv->address.sin_port = htons(port);
    FD_ZERO(&serv->readfds);
    FD_SET(serv->socket_fd, &serv->readfds);
    serv->max_fds = serv->socket_fd;
    serv->fct = array_struct();
    return serv;
}
