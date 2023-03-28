/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** DLLoader
*/

#include "my.h"

void *load_library(void)
{
    void *lib = dlopen("./libs/libmyteams.so", RTLD_LAZY);
    return lib;
}

void *load_library_function(void *lib, char *function_name)
{
    void (*function)(void) = dlsym(lib, function_name);
    return function;
}
