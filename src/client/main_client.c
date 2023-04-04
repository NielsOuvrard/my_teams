/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

void loop(client *cli)
{
    char *message;
    while (1) {
        handle_server_response(cli);
        if (!(message = loop_get_message()))
            return;
        if (send(cli->sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return;
        }
    }
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
    cli.lib = load_library();
    cli.data_lib = load_library_data(cli);
    cli.funct_client = array_struct();
    loop(&cli);
    close(cli.sock);
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
