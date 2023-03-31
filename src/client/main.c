/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

char *get_message(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    if (getline(&line, &len, stdin) == -1)
        return NULL;
    return line;
}

char *loop_get_message(void)
{
    char *message;
    printf("Enter message: ");
    if (!(message = get_message()))
        return NULL;
    if (message[0] == '\n')
        return loop_get_message();
    return message;
}

void loop(int sock)
{
    char *message;
    char server_reply[2000];
    while (1) {
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }
        printf("Server reply: %s\n", server_reply);
        if (!(message = loop_get_message()))
            return;
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return;
        }
    }
}

void help (void)
{
    printf("USAGE: ./client ip port\n\tip");
    printf("\tis the server ip address on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
}

int client (int ac, char **av)
{
    int sock;
    struct sockaddr_in server;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }
    server.sin_addr.s_addr = inet_addr(av[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(av[2]));
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }
    printf("Connected to server\n");
    loop(sock);
    close(sock);
}

int main(int ac, char *av[])
{
    if (ac == 2 && !strncmp(av[1], "-help", 5)) {
        help();
        return 0;
    } else if (ac != 3) {
        printf("./myteams_client -help\n");
        return 84;
    }
    return client(ac, av);
}
