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

#define NB_CLI_FUNCT 29

#define LIST_CLI_FUNC  \
    "client_event_logged_in", \
    "client_event_logged_out", \
    "client_event_private_message_received", \
    "client_event_thread_reply_received", \
    "client_event_team_created", \
    "client_event_channel_created", \
    "client_event_thread_created", \
    "client_print_users", \
    "client_print_teams", \
    "client_team_print_channels", \
    "client_channel_print_threads", \
    "client_thread_print_replies", \
    "client_private_message_print_messages", \
    "client_error_unknown_team", \
    "client_error_unknown_channel", \
    "client_error_unknown_thread", \
    "client_error_unknown_user", \
    "client_error_unauthorized", \
    "client_error_already_exist", \
    "client_print_user", \
    "client_print_team", \
    "client_print_channel", \
    "client_print_thread", \
    "client_print_team_created", \
    "client_print_channel_created", \
    "client_print_thread_created", \
    "client_print_reply_created", \
    "client_print_subscribed", \
    "client_print_unsubscribed"

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
#define CODE_300 "300 create"
#define CODE_400 "400 list"
#define CODE_500 "500 info"

#define LIST_CODE "200", "201", "202", "203", "204", "205", "206", "207", \
    "208", "209", "210", "300", "400", "500",

#define LIST_FUNC \
    &help_function, &login_function, &logout_function, &users_function, \
    &user_function, &send_function, &messages_function, &subscribe_function, \
    &subscribed_function, &unsubscribe_function, &use_function, \
    &create_function, &list_function, &info_function,

#define LIST_COMMANDS \
    "/help", "/login", "/logout", "/users", "/user", "/send", "/messages", \
    "/subscribe", "/subscribed", "/unsubscribe", "/use", "/create", \
    "/list", "/info"

// "230", "231", "232", "233", "234", "235", "236", "400", "401", "402", \
// "403", "404", "405", "406", "407", "408", "409", "410", "411", "412", \
// "413", "414", "415", "510", "511", "512", "513", "514", "515"

#define LIST_TYPE_FUNC  \
    2,2,2,4,3,3,6,8,3,3,7,6,5,1,1,1,1,0,0,8,3,3,7,3,3,7,6,2,2

typedef int (*fct_0)(void);
typedef int (*fct_1)(char const *);
typedef int (*fct_2)(char const *, const char *);
typedef int (*fct_3)(char const *, const char *, const char *);
typedef int (*fct_4)(char const *, const char *, const char *, const char *);
typedef int (*fct_5)(char const *, time_t, const char *);
typedef int (*fct_6)(char const *, const char *, time_t, const char *);
typedef int (*fct_7)(char const *, const char *, time_t, const char *,
const char *);
typedef int (*fct_8)(char const *, const char *, int);

typedef struct fct_lib {
    char *name;
    void *fct;
    int type;
} fct_lib_t;

typedef int (*command_func)(/* ? */);

#define NB_COMMANDS 14

typedef struct fct_client {
    char *name;
    char *code;
    command_func fct;
} fct_client_t;

typedef struct client_t {
    void *lib;
    int sock;
    fct_lib_t *data_lib;
    fct_client_t *funct_client;
} client;

char **my_str_to_word_array(char *str);

void print_array(char **);

char *loop_get_message(void);

void handle_server_response(client *cli);

char **my_str_parse (char *str, char *part);

// array function :

fct_lib_t *load_library_data (client cli);

fct_client_t *array_struct(void);

// * dll

void *load_library(void);

void *load_library_function(void *lib, char *function_name);

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


// int client_event_logged_in(char const *user_uuid, const char *user_name);
// int client_event_logged_out(char const *user_uuid, const char *user_name);
// int client_event_private_message_received();
// int client_event_thread_reply_received();
// int client_event_team_created();
// int client_event_channel_created();
// int client_event_thread_created();

// int client_error_unknown_team(char const *team_uuid);
// int client_error_unknown_channel(char const *channel_uuid);
// int client_error_unknown_thread(char const *thread_uuid);
// int client_error_unknown_user(char const *user_uuid);
// int client_error_unauthorized(void);
// int client_error_already_exist(void);

// int client_print_users();
// int client_print_teams();
// int client_team_print_channels();
// int client_channel_print_threads();
// int client_thread_print_replies();
// int client_private_message_print_messages();
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
