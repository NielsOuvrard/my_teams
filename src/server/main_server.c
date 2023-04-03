/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** main
*/

#include "my_server.h"

void server_loop(server **serv, client **clients)
{
    while (1) {
        fd_set copy_fds = (*serv)->readfds;
        if (select((*serv)->max_fds + 1, &copy_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        handle_new_connection(serv, clients, copy_fds);
        client_communication(serv, clients, copy_fds);
    }
}

// 7 "server_event_user_loaded"
void load_all_users (server *serv, client **clients)
{
    DIR *dir = open_data_users();
    struct dirent *ent;
    char file_path[1024];
    while ((ent = readdir(dir)) != NULL) {
        if (strncmp(ent->d_name, ".", 1) != 0) {
            sprintf(file_path, "%s/%s", "data/users", ent->d_name);
            char *username = filepath_to_str(file_path);
            fct_2 function = serv->array_fct[7];
            function(ent->d_name, username);
            free(username);
        }
    }
    closedir(dir);
}

void my_teams(int port)
{
    server *serv = construct_struct(port);
    client *clients = malloc(sizeof(client) * (MAX_CLIENTS + 1));
    initialize_client(&clients);
    initialize_server(serv->socket_fd, serv->address);
    load_all_users(serv, &clients);
    server_loop(&serv, &clients);
    close(serv->socket_fd);
    shutdown(serv->socket_fd, SHUT_RDWR);
    free(serv);
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
    my_teams(atoi(av[1]));
    return 0;
}
