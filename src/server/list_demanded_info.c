/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** preload_users
*/

#include "my_server.h"

char **get_infos(server *serv, char *file_path)
{
    char *line = NULL;
    size_t len = 0;
    FILE *fd = fopen(file_path, "r");
    char **infos = NULL;
    int i = 0;
    while (getline(&line, &len, fd) != -1) {
        char *tmp = strdup(line);
        infos = realloc(infos, sizeof(char *) * (i + 1));
        infos[i] = tmp;
        i++;
    }
    infos = realloc(infos, sizeof(char *) * (i + 1));
    infos[i] = NULL;
    fclose(fd);
    return infos;
}

void to_exec_or_send(server *serv, char *file_path, char *func_name,
int nbr_args_or_sd)
{
    char **infos = get_infos(serv, file_path);
    if (strcmp(serv->to_do, "exec") == 0) {
        if (nbr_args_or_sd == 2)
            exec_function_2(serv, infos, func_name);
        if (nbr_args_or_sd == 3)
            exec_function_3(serv, infos, func_name);
    } else if (strcmp(serv->to_do, "send") == 0) {
        send_info(infos, nbr_args_or_sd);
    }
}

void get_folder_files(server *serv, char *path, char *func_name,
int nbr_args)
{
    DIR *dir;
    struct dirent *ent;
    char **infos = NULL;
    char file_path[1024];
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(84);
    }
    while ((ent = readdir(dir)) != NULL) {
        if (strncmp(ent->d_name, ".", 1) != 0) {
            snprintf(file_path, sizeof(file_path), "%s/%s", path, ent->d_name);
            to_exec_or_send(serv, file_path, func_name, nbr_args);
        }
    }
    closedir(dir);
}
