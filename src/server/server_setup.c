/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** server_setup
*/

#include "my.h"

int create_socket(void)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

void initialize_server(int socket_fd, struct sockaddr_in address)
{
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }
    if (listen(socket_fd, MAX_CLIENTS) < 0) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }
}

server *construct_struct(int port)
{
    server *serv = malloc(sizeof(server));
    serv->port = port;
    serv->socket_fd = create_socket();
    serv->address.sin_family = AF_INET;
    serv->address.sin_addr.s_addr = INADDR_ANY;
    serv->address.sin_port = htons(port);
    FD_ZERO(&serv->readfds);
    FD_SET(serv->socket_fd, &serv->readfds);
    serv->max_fds = serv->socket_fd;
    serv->lib = load_library();
    serv->root_dir = getcwd(NULL, 0);
    return serv;
}
