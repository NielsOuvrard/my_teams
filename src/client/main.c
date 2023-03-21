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

int main(int ac, char *av[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(av[1]); // IP address of the server
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(av[2])); // Port number of the server

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return 1;
    }

    printf("Connected to server\n");

    // Send some data
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }

        printf("Server reply: %s\n", server_reply);
    }

    close(sock);
    return 0;
}
