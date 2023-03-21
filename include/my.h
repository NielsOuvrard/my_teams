/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** my
*/

#pragma once

#define MAX_CLIENTS 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

typedef struct client_t {
    int socket;
    int connect_data_socket;
    char *username;
    char *password;
    char *current_dir;
    char *old_dir;
    bool is_logged;
    bool is_passive;
    struct sockaddr_in address;
    struct sockaddr_in data_address;
} client;

typedef struct server_t {
    int socket_fd;
    int max_fds;
    int port;
    char *buffer;
    int addlen;
    char *root_dir;
    struct sockaddr_in address;
    fd_set readfds;
} server;

int command_handler(server **serv, client *current_client, int sd);
void handle_pwd(server **serv, client *current_client, int sd);
void handle_cwd(server **serv, client *current_client, int sd);
void handle_username(server **serv, client *current_client, int sd);
void handle_password(server **serv, client *current_client, int sd);
void remove_client(client *clients, int client_fd);
int client_communication(server **serv, client **clients, fd_set copy_fds);
void handle_new_connection(server **serv, client **clients, fd_set copy_fds);
void add_client(client **clients, int socket_fd, struct sockaddr_in address,
char *root_dir);server *construct_struct(int port);
void initialize_server(int socket_fd, struct sockaddr_in address);
void initialize_client(client **clients);
void handle_pasv(server **serv, client *current_client, int sd);
int create_socket(void);
void handle_retr(server **serv, client *current_client, int sd);
void handle_cdup(server **serv, client *current_client, int sd);
void handle_quit(server **serv, client *current_client, int sd);
void handle_list(server **serv, client *current_client, int sd);
void handle_list(server **serv, client *current_client, int sd);
void handle_help(server **serv, client *current_client, int sd);
void handle_dele(server **serv, client *current_client, int sd);
