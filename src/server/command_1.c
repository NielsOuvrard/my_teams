/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_server.h"

int login_function          (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    login_handler(serv, current_client, sd);
    printf("Client %d logged in.\n", sd);
    return 0;
}

int logout_function         (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    logout_handler(serv, current_client, sd);
    printf("Client %d logged out.\n", sd);
    return 0;
}

// code 203
// uuid
// username
// status
int users_function          (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 1, sd))
        return 0;
    DIR *dir = open_data_users();
    struct dirent *ent;
    char **infos = NULL, file_path[1024], to_send[4096];
    strcpy(to_send, CODE_203);
    strcat(to_send, "\n");
    while ((ent = readdir(dir)) != NULL) {
        if (strncmp(ent->d_name, ".", 1) != 0) {
            sprintf(file_path, "%s%s", "data/users/", ent->d_name);
            char tmp[1024];
            char *username = filepath_to_str(file_path);
            sprintf(tmp, "%s\n%s\n%d\n", ent->d_name, username,
            client_is_logged(cli_list, ent->d_name));
            strcat(to_send, tmp);
        }
    }
    send(sd, to_send, strlen(to_send), 0);
    closedir(dir);
    return 0;
}

int user_function           (server **serv, client **cli_list,
                            client *curr_cli, int sd)
{
    if (user_not_connected(curr_cli) || !args_check((*serv)->command, 2, sd))
        return 0;
    char filepath[1024];
    sprintf(filepath, "%s%s", "data/users/", (*serv)->command[1]);
    char *username = filepath_to_str(filepath);
    char *infos[5];
    infos[0] = CODE_204;
    infos[1] = (*serv)->command[1];
    infos[2] = username;
    infos[3] = client_is_logged(cli_list, (*serv)->command[1]) ? "1" : "0";
    infos[4] = NULL;
    send_info_client(infos, sd);
    return 0;
}

int send_function           (server **serv, client **cli_list,
                            client *current_client, int sd)
{
    return 0;
}
