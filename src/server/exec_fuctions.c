/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** exec_fuctions
*/

#include "my.h"

void exec_function_2(server *serv, char **infos, char *func_name)
{
    void *function =
    load_library_function(serv->lib, func_name);
    ((int (*)(char const *, char const *))function)
    (my_str_to_word_array(infos[0])[1],
    my_str_to_word_array(infos[1])[1]);
}

void exec_function_3(server *serv, char **infos, char *func_name)
{
    void *function =
    load_library_function(serv->lib, func_name);
    ((int (*)(char const *, char const *, char const *))function)
    (my_str_to_word_array(infos[0])[1],
    my_str_to_word_array(infos[1])[1], my_str_to_word_array(infos[2])[1]);
}
