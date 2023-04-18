/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

int loop_client (client *cli, fd_set read_fds, int *server_reply,
struct timeval tv)
{
    char *message = NULL;
    fd_set tmp_fds = read_fds;
    if (select(cli->sock + 1, &tmp_fds, NULL, NULL, &tv) < 0) {
        perror("Erro na função select");
        exit(EXIT_FAILURE);
    }
    if (FD_ISSET(cli->sock, &tmp_fds)) {
        *server_reply = handle_server_response(cli);
    }
    if (*server_reply == -1 || *server_reply == 84) {
        printf("Server disconnected\n");
        return -1;
    }
    if (FD_ISSET(STDIN_FILENO, &tmp_fds)) {
        message = loop_get_message(NULL);
        send(cli->sock, message, strlen(message), 0);
        free(message);
    }
    return 0;
}

int loop(client *cli)
{
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(cli->sock, &read_fds); FD_SET(STDIN_FILENO, &read_fds);
    struct timeval tv;
    tv.tv_sec = 0; tv.tv_usec = 10000;
    int server_reply = 0;
    while (1)
        if (loop_client(cli, read_fds, &server_reply, tv) == -1)
            return server_reply;
    return 0;
}

int help (void)
{
    printf("USAGE: ./client ip port\n\tip");
    printf("\tis the server ip address on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
    return 0;
}

int client_funct (int ac, char **av)
{
    client cli;
    cli.is_connected = false;
    struct sockaddr_in server;
    cli.sock = socket(AF_INET, SOCK_STREAM, 0);
    if (cli.sock == -1)
        printf("Could not create socket");
    server.sin_addr.s_addr = inet_addr(av[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(av[2]));
    if (connect(cli.sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    cli.funct_client = array_struct();
    int server_reply = loop(&cli);
    free(cli.funct_client);
    close(cli.sock);
    if (server_reply == 84)
        return 84;
    return 0;
}

int main(int ac, char *av[])
{
    if (ac == 2 && !strncmp(av[1], "-help", 5)) {
        return help();
    } else if (ac != 3) {
        printf("./myteams_client -help\n");
        return 84;
    }
    return client_funct(ac, av);
}
