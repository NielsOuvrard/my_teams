/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** server_setup
*/

#include "my_server.h"

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

void **array_fct(void)
{
    void *lib = load_library();
    char *names_functs[NB_SERVER_FUNCT] = { LIST_SERV_FUNC };
    void **array_fct = malloc(sizeof(void *) * NB_SERVER_FUNCT);
    for (int i = 0; i < NB_SERVER_FUNCT; i++) {
        array_fct[i] = dlsym(lib, names_functs[i]);
    }
    return array_fct;
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
    serv->fct = array_struct();
    serv->array_fct = array_fct();
    return serv;
}
