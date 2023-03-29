/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** write_in_file
*/

#include "my.h"

void write_in_file(char *file, char *str)
{
    FILE *fp = fopen(file, "a+");
    if (fp == NULL) {
        exit(1);
    }
    fprintf(fp, "%s", str);
    fclose(fp);
}
