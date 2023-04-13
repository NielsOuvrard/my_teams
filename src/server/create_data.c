/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** connection_handler
*/

#include "my_server.h"

// create_team(serv, cli_list, cli, sd);
// create_channel(serv, cli_list, cli, sd);
// create_thread(serv, cli_list, cli, sd);
// create_reply(serv, cli_list, cli, sd);


// uuid_generate(cli->uuid);
// uuid_unparse(cli->uuid, cli->uuid_text);

// wow... thanks copilot
// int create_team (server **serv, client **cli_list, client *cli, int sd)
// {
//     char *team_name = (*serv)->command[1];
//     char *team_description = (*serv)->command[2];
//     // char *uuid, uuid_text[37];
//     // uuid_generate(uuid);
//     // uuid_unparse(uuid, uuid_text);
//     if (!team_name || !team_description)
//         return 0;
//     if (strlen(team_name) > MAX_NAME_LENGTH ||
//         strlen(team_description) > MAX_DESCRIPTION_LENGTH)
//         return 0;
//     // if (get_team_by_name(serv, team_name))
//     //     return 0;
//     char *uuid = generate_uuid();
//     char *query = malloc(sizeof(char) * 1024);
//     sprintf(query, "INSERT INTO teams (uuid, name, description) VALUES ('%s', '%s', '%s')", uuid, team_name, team_description);
//     sqlite3_exec((*serv)->db, query, NULL, NULL, NULL);
//     char *response = malloc(sizeof(char) * 1024);
//     sprintf(response, "team_created \"%s\" \"%s\" \"%s\"", uuid, team_name, team_description);
//     send(sd, response, strlen(response), 0);
//     return 0;
// }

// // uuid_team TEXT, uuid TEXT, name TEXT, description TEXT
// int create_channel (server **serv, client **cli_list, client *cli, int sd)
// {
//     char *uuid_team = (*serv)->command[1];
//     // char *uuid = (*serv)->command[2];
//     char *name = (*serv)->command[3];
//     char *description = (*serv)->command[4];
//     // char *team_name = (*serv)->command[1];
//     // char *team_description = (*serv)->command[2];
//     if (array_len((*serv)->command) != 5)
//         return 0;
//     if (strlen(name) > MAX_NAME_LENGTH ||
//         strlen(description) > MAX_DESCRIPTION_LENGTH)
//         return 0;
//     // if (get_team_by_name(serv, team_name))
//     //     return 0;
//     char *uuid = generate_uuid();
//     char *query = malloc(sizeof(char) * 1024);
//     sprintf(query, "INSERT INTO channels (uuid_team, uuid, name, description) VALUES ('%s', '%s', '%s', '%s')", uuid_team, uuid, name, description);
//     sqlite3_exec((*serv)->db, query, NULL, NULL, NULL);
//     char *response = malloc(sizeof(char) * 1024);
//     sprintf(response, "team_created \"%s\" \"%s\" \"%s\"", uuid, name, description);
//     send(sd, response, strlen(response), 0);
//     return 0;
// }

// // uuid_team TEXT, uuid_channel TEXT, uuid TEXT, name TEXT, description TEXT
// int create_thread (server **serv, client **cli_list, client *cli, int sd)
// {
//     // char *team_name = (*serv)->command[1];
//     // char *team_description = (*serv)->command[2];
//     char *uuid_team = (*serv)->command[1];
//     char *uuid_channel = (*serv)->command[2];
//     char *name = (*serv)->command[4];
//     char *description = (*serv)->command[5];
//     if (array_len((*serv)->command) != 6)
//         return 0;
//     if (strlen(name) > MAX_NAME_LENGTH ||
//         strlen(description) > MAX_DESCRIPTION_LENGTH)
//         return 0;
//     // if (get_team_by_name(serv, team_name))
//     //     return 0;
//     char *uuid = generate_uuid();
//     char *query = malloc(sizeof(char) * 1024);
//     sprintf(query, "INSERT INTO threads (uuid_team, uuid_channel, uuid, name, description) VALUES ('%s', '%s', '%s', '%s', '%s')",
//             uuid_team, uuid_channel, uuid, name, description);
//     sqlite3_exec((*serv)->db, query, NULL, NULL, NULL);
//     char *response = malloc(sizeof(char) * 1024);
//     sprintf(response, "team_created \"%s\" \"%s\" \"%s\"", uuid, name, description);
//     send(sd, response, strlen(response), 0);
//     return 0;
// }

// int create_reply (server **serv, client **cli_list, client *cli, int sd)
// {
//     // ?
//     return 0;
// }

