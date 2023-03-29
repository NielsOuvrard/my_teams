/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** main
*/

#include "my.h"

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

char **read_file(void)
{
    char *line = NULL;
    char **users = malloc(sizeof(char *) * 1);
    int i = 0;
    size_t len = 0;
    FILE *fd = fopen("data/.users", "r");
    while (getline(&line, &len, fd) != -1) {
        users = realloc(users, sizeof(char *) * (i + 1));
        users[i] = strdup(line);
        i++;
    }
    fclose(fd);
    users[i] = NULL;
    return users;
}

void initialize_save_client(client **clients, int cur_user, char **user)
{
    for (int j = 0; user[j] != NULL; j++) {
        if (strcmp(user[j], "##USER") == 0) {
            (*clients)[cur_user].username = strdup(user[j + 1]);
            (*clients)[cur_user].already_subscribed = true;
            j++;
            continue;
        }
        if (strcmp(user[j], "##UUID") == 0) {
            (*clients)[cur_user].uuid_text = strdup(user[j + 1]);
            j++;
            continue;
        }
    }
}

client *load_users(server *serv)
{
    if (access("data/.users", F_OK) == -1)
        return NULL;
    client *clients = malloc(sizeof(client) * (MAX_CLIENTS + 1));
    char **users = read_file();
    for (int i = 0, cur_user = 0; users[i] != NULL; i++, cur_user++) {
        char **user = my_str_to_word_array(users[i]);
        initialize_save_client(&clients, cur_user, user);
    }
    void *function = load_library_function(serv->lib,
    "server_event_user_loaded");
    for (int i = 0; i != MAX_CLIENTS; i++) {
        if (clients[i].username != NULL) {
            ((int (*)(char const *, char const *))function)
            (clients[i].uuid_text, clients[i].username);
        }
    }
}

void my_teams(int port)
{
    server *serv = construct_struct(port);
    client *clients = malloc(sizeof(client) * (MAX_CLIENTS + 1));
    initialize_client(&clients);
    initialize_server(serv->socket_fd, serv->address);
    serv->saved_cli = load_users(serv);
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
