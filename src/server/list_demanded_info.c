/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** preload_users
*/

#include "my.h"

//make it generic

void preload_infos(server *serv, char *file_path)
{
    char *line = NULL;
    size_t len = 0;
    void *function;
    FILE *fd = fopen(file_path, "r");
    char **infos = malloc(sizeof(char *) * 1);
    int i = 0;
    while (getline(&line, &len, fd) != -1) {
        infos[i] = strdup(line);
        infos = realloc(infos, sizeof(char *) * (i + 1));
        i++;
    }
    infos[i] = NULL;
    function =
    load_library_function(serv->lib, "server_event_user_loaded");
    ((void (*)(char const *, char const *))function)
    (my_str_to_word_array(infos[0])[1],
    my_str_to_word_array(infos[1])[1]);
    fclose(fd);
}

void folder_files(server *serv, char *path)
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
            preload_infos(serv, file_path);
        }
    }
    closedir(dir);
}

void preload_users(server *serv)
{
    folder_files(serv, "data/users/");
}
