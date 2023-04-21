/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

int client_funct (int ac, char **av);

int help (void)
{
    printf("USAGE: ./client ip port\n\tip");
    printf("\tis the server ip address on which the server socket listens.\n");
    printf("\tport\tis the port number on which the server socket listens.\n");
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
