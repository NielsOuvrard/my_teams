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

#define NB_CLI_FUNCT 29
// int client_event_logged_in(char const *user_uuid, const char *user_name);
// int client_event_logged_out(char const *user_uuid, const char *user_name);
// int client_event_private_message_received(
// int client_event_thread_reply_received(
// int client_event_team_created(
// int client_event_channel_created(
// int client_event_thread_created(
// int client_print_users(
// int client_print_teams(
// int client_team_print_channels(
// int client_channel_print_threads(
// int client_thread_print_replies(
// int client_private_message_print_messages(
// int client_error_unknown_team(char const *team_uuid);
// int client_error_unknown_channel(char const *channel_uuid);
// int client_error_unknown_thread(char const *thread_uuid);
// int client_error_unknown_user(char const *user_uuid);
// int client_error_unauthorized(void);
// int client_error_already_exist(void);
// int client_print_user(
// int client_print_team(
// int client_print_channel(
// int client_print_thread(
// int client_print_team_created(
// int client_print_channel_created(
// int client_print_thread_created(
// int client_print_reply_created(
// int client_print_subscribed(char const *user_uuid, char const *team_uuid);
// int client_print_unsubscribed(char const *user_uuid, char const *team_uuid);

#define CODE_200 "200 Command okay.\r\n"
#define CODE_214 "214 Help message.\r\n"
#define CODE_220 "220 Service ready for new user.\r\n"
// ? #define CODE_221 "221 Service closing control connection.\r\n"
// ? #define CODE_226 "226 Closing data connection.\r\n"

// * event
#define CODE_230 "230 User logged in, proceed.\r\n"
#define CODE_231 "231 User logged out\r\n"
#define CODE_232 "232 Private message received\r\n"
#define CODE_233 "233 A new reply is posted in a thread\r\n"
#define CODE_234 "234 A new team is created\r\n"
#define CODE_235 "235 A new channel is created\r\n"
#define CODE_236 "236 A new thread is created\r\n"
// #define CODE_305 "305 A new user is subscribed to a team\r\n"
// #define CODE_306 "306 A user is unsubscribed from a team\r\n"
// #define CODE_307 "307 A new user is created\r\n"
// #define CODE_308 "308 A user is deleted\r\n"

// * print
#define CODE_400 "400 print users\r\n"
#define CODE_401 "401 print teams\r\n"
#define CODE_402 "402 print team channels\r\n"
#define CODE_403 "403 print channel threads\r\n"
#define CODE_404 "404 print thread replies\r\n"
#define CODE_405 "405 print private messages\r\n"
#define CODE_406 "406 print user\r\n"
#define CODE_407 "407 print team\r\n"
#define CODE_408 "408 print channel\r\n"
#define CODE_409 "409 print thread\r\n"
#define CODE_410 "410 print team created\r\n"
#define CODE_411 "411 print channel created\r\n"
#define CODE_412 "412 print thread created\r\n"
#define CODE_413 "413 print reply created\r\n"
#define CODE_414 "414 print subscribed\r\n"
#define CODE_415 "415 print unsubscribed\r\n"

// * error
#define CODE_510 "510 Unknown team.\r\n"
#define CODE_511 "511 Unknown channel.\r\n"
#define CODE_512 "512 Unknown thread.\r\n"
#define CODE_513 "513 Unknown user.\r\n"
#define CODE_514 "514 Unauthorized.\r\n"
#define CODE_515 "515 The resource already exist.\r\n"
// #define CODE_500 "500 Syntax error, command unrecognized.\r\n"
// #define CODE_501 "501 Syntax error in parameters or arguments.\r\n"
// #define CODE_502 "502 Command not implemented.\r\n"
// #define CODE_503 "503 Bad sequence of commands.\r\n"
// #define CODE_504 "504 Command not implemented for that parameter.\r\n"
// #define CODE_530 "530 Not logged in.\r\n"

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
    char *to_do;
    struct sockaddr_in address;
    fd_set readfds;
    fct_server_t *fct;
} server;

void command_handler(server **serv, client **cli_list,
client *current_client, int sd);

// int fct(char const *);
// int fct(char const *, const char *);
// int fct(char const *, const char *, const char *);
// int fct(char const *, const char *, const char *, const char *, const char *);

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
void user_list_handler(server **serv, client **cli_list,
client *current_client, int sd);

//load infos
char **load_infos(char *file_path);
char **find_content(char *file_path, char *loking_for);
char **read_folder_files(char *path, char *loking_for);

void get_folder_files(server *serv, char *path, char *func_name,
int nbr_args);

//exec func
void exec_function_2(server *serv, char **infos, char *func_name);
void exec_function_3(server *serv, char **infos, char *func_name);

//send
void send_info(char **infos, int sd);
