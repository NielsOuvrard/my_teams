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
#include <stdarg.h>




typedef struct client_t client;
typedef struct server_t server;

typedef int (*command_func)(server **serv, client **cli_list,
client *current_client, int sd);

#define NB_COMMANDS 14

typedef struct fct_server {
    char *name;
    command_func fct;
} fct_server_t;

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
    fct_server_t *fct;
} server;

void command_handler(server **serv, client **cli_list,
client *current_client, int sd);

// * Command functions
// • /login [“user_name”] : set the user_name used by client
int login_function          (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /logout : disconnect the client from the server
int logout_function         (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /users : get the list of all users that exist on the domain
int users_function          (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /user [“user_uuid”] : get details about the requested user
int user_function           (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /send [“user_uuid”] [“message_body”] : send a message to specific user
int send_function           (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /messages [“user_uuid”] : list all messages exchanged with the specified
//      user
int messages_function       (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /subscribe [“team_uuid”] : subscribe to the events of a team and its sub
//      directories (enable reception of all events from a team)
int subscribe_function      (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /subscribed ?[“team_uuid”] : list all subscribed teams or list all users
//      subscribed to a team
int subscribed_function     (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /unsubscribe [“team_uuid”] : unsubscribe from a team
int unsubscribe_function    (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the
//      command context to a team/channel/thread
int use_function            (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /create : based on the context, create the sub resource (see below)
int create_function         (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /list : based on the context, list all the sub resources (see below)
int list_function           (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /info : based on the context, display details of the current resource
//      (see below
int info_function           (server **serv, client **cli_list,
                            client *current_client, int sd);

// • /help : show help
int help_function           (server **serv, client **cli_list,
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

void print_map(char **map);

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
void replace_line_file(char *find, char *new, char *file);

//user or users
void users_list_handler(server **serv, client **cli_list,
client *current_client, int sd);

//load infos
char **load_infos(char *file_path);
char **find_content(char *file_path, char *loking_for);
char **read_folder_files(char *path, char *loking_for);

void get_folder_files(server *serv, char *path, char *func_name,
int nbr_args, char *to_do);
