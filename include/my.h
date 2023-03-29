/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** my
*/

#pragma once

#define MAX_CLIENTS 100
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

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
#include <uuid/uuid.h>
#include <dlfcn.h>

typedef struct client_t {
    int socket;
    char *username;
    bool is_logged;
    struct sockaddr_in address;
    uuid_t uuid;
    char *uuid_text;
    bool already_subscribed;
} client;

typedef struct server_t {
    int socket_fd;
    int max_fds;
    int port;
    char **command;
    int addlen;
    void *lib;
    struct sockaddr_in address;
    fd_set readfds;
} server;

void command_handler(server **serv, client **cli_list,
client *current_client, int sd);

void remove_client(client *clients, int client_fd);

int client_communication(server **serv, client **clients, fd_set copy_fds);

void handle_new_connection(server **serv, client **clients, fd_set copy_fds);

void add_client(client **clients, int socket_fd, struct sockaddr_in address);

server *construct_struct(int port);

void initialize_server(int socket_fd, struct sockaddr_in address);

void initialize_client(client **clients);

int create_socket(void);

char **get_command(int sd);

char **my_str_to_word_array(char *str);

//preload users
void preload_users(server *serv);

//login
void login_handler(server **serv, client *current_client, int sd);

//logout
void logout_handler(server **serv, client *current_client, int sd);

//DLLoader
void *load_library(void);
void *load_library_function(void *lib, char *function_name);

//checks
bool args_check(char **command, int nb_args, int sd);
bool user_connected(client *current_client);
bool user_not_connected(client *current_client);
bool check_user_already_subscribed(client *current_client);

//file
void write_in_file(char *file, char *str);

//user or users
void users_list_handler(server **serv, client **cli_list,
client *current_client, int sd);

//load infos
char **load_infos(char *file_path);
char **find_content(char *file_path, char *loking_for);
char **read_folder_files(char *path, char *loking_for);
