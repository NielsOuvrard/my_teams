/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

void *load_library(void)
{
    void *lib = dlopen("./libs/myteams/libmyteams.so", RTLD_NOW);
    return lib;
}

void *load_library_function(void *lib, char *function_name)
{
    void (*function)(void) = dlsym(lib, function_name);
    return function;
}

void exec_function_2(client *cli, char **infos, char *func_name)
{
    void *function = load_library_function(cli->lib, func_name);
    ((function_2) function)(infos[0], infos[1]);
}

void exec_function_3(client *cli, char **infos, char *func_name)
{
    void *function = load_library_function(cli->lib, func_name);
    ((function_3) function)(infos[0], infos[1], infos[2]);
}
