/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** main
*/

#include "my_client.h"

fct_client_t *array_struct(void)
{
    char *commandes[NB_COMMANDS] = { LIST_COMMANDS };
    char *code[NB_COMMANDS] = { LIST_CODE };
    command_func fptr[NB_COMMANDS] = { LIST_FUNC };
    fct_client_t *fct = malloc(sizeof(fct_client_t) * NB_COMMANDS);
    for (int i = 0; i < NB_COMMANDS; i++) {
        fct[i].name = commandes[i];
        fct[i].fct = fptr[i];
        fct[i].code = code[i];
    }
    return fct;
}
