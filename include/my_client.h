/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-gabriel.de-souza-morais
** File description:
** my
*/

#pragma once

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

#include "logging_client.h"

typedef int (*function_2)(char const *, char const *);
typedef int (*function_3)(char const *, char const *, char const *);

typedef struct client_t {
    void *lib;
    int sock;
} client;

char **my_str_to_word_array(char *str);

void print_map(char **map);

char *loop_get_message(void);

void handle_server_response(client *cli);

char **my_str_parse (char *str, char *part);

void print_map(char **map);


// * dll

void *load_library(void);

void *load_library_function(void *lib, char *function_name);

void exec_function_2(client *cli, char **infos, char *func_name);

void exec_function_3(client *cli, char **infos, char *func_name);
