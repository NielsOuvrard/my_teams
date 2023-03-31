/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** write_in_file
*/

#include "my_server.h"

void replace_line_file(char *find, char *new, char *file)
{
    FILE *fd = fopen(file, "r+");
    if (file == NULL) {
        perror("fopen");
        exit (84);
    }
    char line[256];
    long offset = 0;
    while (fgets(line, sizeof(line), fd)) {
        if (strstr(line, find)) {
            fseek(fd, offset, SEEK_SET);
            fputs(new, fd);
            break;
        }
        offset = ftell(fd);
    }
    fclose(fd);
}

void write_in_file(char *file, char *str)
{
    FILE *fp = fopen(file, "a+");
    if (fp == NULL) {
        exit(1);
    }
    fprintf(fp, "%s", str);
    fclose(fp);
}
