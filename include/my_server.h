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

#include "logging_server.h"

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
#include <sqlite3.h>
#include <time.h>

#define CODE_200 "200 help\n"
#define CODE_201 "201 login\n"
#define CODE_202 "202 logout\n"
#define CODE_203 "203 users\n"
#define CODE_204 "204 user\n"
#define CODE_205 "205 send\n"
#define CODE_206 "206 messages\n"
#define CODE_207 "207 subscribe\n"
#define CODE_208 "208 subscribed\n"
#define CODE_209 "209 unsubscribe\n"
#define CODE_210 "210 use\n"
#define CODE_211 "211 create_team\n"
#define CODE_212 "212 create_channel\n"
#define CODE_213 "213 create_thread\n"
#define CODE_214 "214 create_reply\n"
#define CODE_215 "215 list\n"
#define CODE_216 "216 info\n"
#define CODE_500 "500 client_error_unknown_team\n"
#define CODE_501 "501 client_error_unknown_channel\n"
#define CODE_502 "502 client_error_unknown_thread\n"
#define CODE_503 "503 client_error_unknown_user\n"
#define CODE_504 "504 client_error_unauthorized\n"
#define CODE_505 "505 client_error_already_exist\n"

#define CODE_220 "220 connected_to_server\n"
#define CODE_221 "221 message_sent_to_receiver\n"
#define CODE_331 "331 user_already_logged\n"
#define CODE_590 "590 command_invalid_arguments\n"
#define CODE_506 "506 create_command_error\n"

#define CREATE_USERS_DB "CREATE TABLE IF NOT EXISTS users \
(id INTEGER PRIMARY KEY, uuid TEXT, username TEXT, connected NUMBER);"

#define CREATE_MESSAGES_DB " CREATE TABLE IF NOT EXISTS messages \
(id INTEGER PRIMARY KEY, sender TEXT, receiver TEXT, message TEXT, \
timestamp TEXT);"

#define CREATE_TEAMS_DB "CREATE TABLE IF NOT EXISTS teams \
(id INTEGER PRIMARY KEY, uuid TEXT, name TEXT, description TEXT);"

#define CREATE_CHANNELS_DB "CREATE TABLE IF NOT EXISTS channels \
(id INTEGER PRIMARY KEY, uuid TEXT, team TEXT, name TEXT, description TEXT);"

#define CREATE_THREADS_DB "CREATE TABLE IF NOT EXISTS threads \
(id INTEGER PRIMARY KEY, uuid TEXT, channel TEXT, user TEXT, title TEXT,\
body TEXT, timestamp TEXT);"

#define CREATE_REPLIES_DB "CREATE TABLE IF NOT EXISTS replies \
(id INTEGER PRIMARY KEY, thread TEXT, user TEXT, body TEXT, \
timestamp TEXT);"

#define NB_COMMANDS 14

#define COMMANDS_NAME \
    "/help", "/login", "/logout", "/users", "/user", \
    "/send", "/messages", "/subscribe", "/subscribed", \
    "/unsubscribe", "/use", "/create", "/list", "/info"

#define COMMANDS_FCT \
    &help_function, &login_function, &logout_function, &users_function, \
    &user_function, &send_function, &messages_function, &subscribe_function, \
    &subscribed_function, &unsubscribe_function, &use_function, \
    &create_function, &list_function, &info_function, \

typedef struct client_t client;
typedef struct server_t server;

typedef int (*command_func)(server **, client **, client *, int sd);

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
    char *team;
    char *channel;
    char *thread;
} client;

typedef struct server_t {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int socket_fd;
    int max_fds;
    int port;
    char **command;
    int addlen;
    struct sockaddr_in address;
    fd_set readfds;
    fct_server_t *fct;
} server;

void command_handler(server **serv, client **cli_list,
client *current_client, int sd);


// * Command functions
// • /login [“user_name”] : set the user_name used by client
int login_function          (server **, client **, client *, int);

// • /logout : disconnect the client from the server
int logout_function         (server **, client **, client *, int);

// • /users : get the list of all users that exist on the domain
int users_function          (server **, client **, client *, int);

// • /user [“user_uuid”] : get details about the requested user
int user_function           (server **, client **, client *, int);

// • /send [“user_uuid”] [“message_body”] : send a message to specific user
int send_function           (server **, client **, client *, int);

// • /messages [“user_uuid”] : list all messages exchanged with the specified
//      user
int messages_function       (server **, client **, client *, int);

// • /subscribe [“team_uuid”] : subscribe to the events of a team and its sub
//      directories (enable reception of all events from a team)
int subscribe_function      (server **, client **, client *, int);

// • /subscribed ?[“team_uuid”] : list all subscribed teams or list all users
//      subscribed to a team
int subscribed_function     (server **, client **, client *, int);

// • /unsubscribe [“team_uuid”] : unsubscribe from a team
int unsubscribe_function    (server **, client **, client *, int);

// • /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the
//      command context to a team/channel/thread
int use_function            (server **, client **, client *, int);

// • /create : based on the context, create the sub resource (see below)
int create_function         (server **, client **, client *, int);

// • /list : based on the context, list all the sub resources (see below)
int list_function           (server **, client **, client *, int);

// • /info : based on the context, display details of the current resource
//      (see below
int info_function           (server **, client **, client *, int);

// • /help : show help
int help_function           (server **, client **, client *, int);

void remove_client(client *clients, int client_fd);

int client_communication(server **serv, client **clients, fd_set copy_fds);

void handle_new_connection(server **serv, client **clients, fd_set copy_fds);

void add_client(client **clients, int socket_fd, struct sockaddr_in address);

server *construct_struct(int port);

DIR *open_data_users(void);

char **get_infos(server *serv, char *file_path);

void initialize_server(int socket_fd, struct sockaddr_in address);

void initialize_client(client **clients);

int client_is_logged(client **clients, char *uuid_text);

int create_socket(void);

char **get_command(int sd);

void error_sql(server *serv, char *error);

void change_status_user (server **serv, const char *uuid_text, int status);

// * Utils

char **my_str_to_word_array(char *str);

char *filepath_to_str(char *filepath);

void free_my_array (char **array);

void print_map(char **map);

int nmb_char_in_array (char **array);

int array_len (char **array);

int send_info_client (char **infos, int sd);

//preload users
void preload_users(server *serv);

//login
int login_handler(server **serv, client *current_client, int sd);

//logout
void logout_handler(server **serv, client *current_client, int sd);

//checks
bool args_check(char **command, int nb_args, int sd);
bool user_connected(client *current_client);
bool user_not_connected(client *current_client);
bool check_if_user_exist(server **se, int sd);
bool check_if_uuid_exists(char *uuid, char *table, sqlite3 *db);
bool check_if_name_exists(char *uuid, char *table, sqlite3 *db);

//user or users
void users_list_handler(server **serv, client **cli_list,
client *current_client, int sd);
void user_list_handler(server **serv, client **cli_list,
client *current_client, int sd);

void get_folder_files(server *serv, char *path, char *func_name,
int nbr_args);

// //exec func
// void exec_function_2(server *serv, char **infos, char *func_name);
// void exec_function_3(server *serv, char **infos, char *func_name);

//send
void send_info(char **infos, int sd);
int send_handler(server **serv, client **cli_list,
client *curr_cli, int sd);
int messages_handler(server **serv, client **cli_list,
client *curr_cli, int sd);

int find_message_receiver(server **serv, client **clients);

//mesage into db
void save_message_in_db(server **serv, client *curr_cli);

//load db
void initialize_message_db(server **serv);
void initialize_user_db(server **serv);
void initialize_db(server **serv);

// looking for uuid

char *get_team_by_uuid (server **, char *);

char *get_channel_by_uuid (server **, char *, char *);

char *get_thread_by_uuid (server **, char *, char *, char *);

//create

int create_team (server **serv, client **cli_list, client *cli, int sd);

int create_channel (server **serv, client **cli_list, client *cli, int sd);

int create_thread (server **serv, client **cli_list, client *cli, int sd);

int create_reply (server **serv, client **cli_list, client *cli, int sd);

char *generate_uuid(void);

//create
int create_handler(server **se, client **cli_list, client *curr_cli, int sd);
