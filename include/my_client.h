/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** my
*/

#pragma once

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

#include "logging_client.h"

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

#define CODE_200 "200 help"
#define CODE_201 "201 login"
#define CODE_202 "202 logout"
#define CODE_203 "203 users"
#define CODE_204 "204 user"
#define CODE_205 "205 send"
#define CODE_206 "206 messages"
#define CODE_207 "207 subscribe"
#define CODE_208 "208 subscribed"
#define CODE_209 "209 unsubscribe"
#define CODE_210 "210 use"
#define CODE_211 "211 create_team\n"
#define CODE_212 "212 create_channel\n"
#define CODE_213 "213 create_thread\n"
#define CODE_214 "214 create_reply\n"
#define CODE_215 "215 list\n"
#define CODE_216 "216 info\n"
#define CODE_230 "230 already_subscribed\n"

// error
#define CODE_500 "500 unknown_team"
#define CODE_501 "501 unknown_channel"
#define CODE_502 "502 unknown_thread"
#define CODE_503 "503 unknown_user"
#define CODE_504 "504 unauthorized"
#define CODE_505 "505 already_exist"

#define NB_COMMANDS 20

#define LIST_CODE "200", "201", "202", "203", "204", "205", "206", "207", \
    "208", "209", "210", "211", "212", "213", "500", "501", "502", "503", \
    "504", "505"

#define LIST_FUNC \
    &help_function, &login_function, &logout_function, &users_function, \
    &user_function, &send_function, &messages_function, &subscribe_function, \
    &subscribed_function, &unsubscribe_function, &use_function, \
    &create_function, &list_function, &info_function, \
    &unknown_team_function, &unknown_channel_function, \
    &unknown_thread_function, &unknown_user_function, \
    &unauthorized_function, &already_exist_function


#define LIST_COMMANDS \
    "/help", "/login", "/logout", "/users", "/user", "/send", "/messages", \
    "/subscribe", "/subscribed", "/unsubscribe", "/use", "/create", \
    "/list", "/info"

typedef int (*command_func)(/* ? */);

typedef struct fct_client {
    char *name;
    char *code;
    command_func fct;
} fct_client_t;

typedef struct client_t {
    char *name;
    char *uuid;
    bool is_connected;
    int sock;
    fct_client_t *funct_client;
    // define context server side my dear
} client;

char **my_str_to_word_array(char *str);

void print_array(char **);

char *loop_get_message(char *str);

void handle_server_response(client *cli);

char **my_str_parse (char *str, char *part);

// array function :

fct_client_t *array_struct(void);

// • /login [“user_name”] : set the user_name used by client
int login_function          (client *cli, char **array);

// • /logout : disconnect the client from the server
int logout_function         (client *cli, char **array);

// • /users : get the list of all users that exist on the domain
int users_function          (client *cli, char **array);

// • /user [“user_uuid”] : get details about the requested user
int user_function           (client *cli, char **array);

// • /send [“user_uuid”] [“message_body”] : send a message to specific user
int send_function           (client *cli, char **array);

// • /messages [“user_uuid”] : list all messages exchanged with the specified
//      user
int messages_function       (client *cli, char **array);

// • /subscribe [“team_uuid”] : subscribe to the events of a team and its sub
//      directories (enable reception of all events from a team)
int subscribe_function      (client *cli, char **array);

// • /subscribed ?[“team_uuid”] : list all subscribed teams or list all users
//      subscribed to a team
int subscribed_function     (client *cli, char **array);

// • /unsubscribe [“team_uuid”] : unsubscribe from a team
int unsubscribe_function    (client *cli, char **array);

// • /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the
//      command context to a team/channel/thread
int use_function            (client *cli, char **array);

// • /create : based on the context, create the sub resource (see below)
int create_function         (client *cli, char **array);

// • /list : based on the context, list all the sub resources (see below)
int list_function           (client *cli, char **array);

// • /info : based on the context, display details of the current resource
int info_function           (client *cli, char **array);

// • /help : show help
int help_function           (client *cli, char **array);

// error

int unknown_team_function   (client *cli, char **array);

int unknown_channel_function(client *cli, char **array);

int unknown_thread_function (client *cli, char **array);

int unknown_user_function   (client *cli, char **array);

int unauthorized_function   (client *cli, char **array);

int already_exist_function  (client *cli, char **array);
