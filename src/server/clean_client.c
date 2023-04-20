/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

void clean_use_client (client *current_client)
{
    if (current_client->channel)
        free(current_client->channel);
    if (current_client->thread)
        free(current_client->thread);
    if (current_client->team)
        free(current_client->team);
    current_client->channel = NULL;
    current_client->thread = NULL;
    current_client->team = NULL;
}
