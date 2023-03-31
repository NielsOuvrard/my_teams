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

char **my_str_to_word_array(char *str);

void print_map(char **map);

char *loop_get_message(void);
