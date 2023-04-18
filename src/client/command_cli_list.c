/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

int list_team_function (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 3) {
        if (!array[i + 1] || !array[i + 2])
            return 0;
        char *team_uuid = array[i];
        char *team_name = array[i + 1];
        char *team_description = array[i + 2];
        client_print_teams(team_uuid, team_name, team_description);
    }
    return 0;
}

int list_channel_function (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 3) {
        if (!array[i + 1] || !array[i + 2])
            return 0;
        char *channel_uuid = array[i];
        char *channel_name = array[i + 1];
        char *channel_description = array[i + 2];
        client_team_print_channels(channel_uuid, channel_name, channel_description);
    }
    return 0;
}

int list_thread_function (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 5) {
        if (!array[i + 1] || !array[i + 2] || !array[i + 3] || !array[i + 4])
            return 0;
        char *t_uuid = array[i];
        char *user_uuid = array[i + 1];
        char *t_timestamp = array[i + 2];
        char *t_title = array[i + 3];
        char *t_body = array[i + 4];
        struct tm tm;
        strptime(t_timestamp, "%a %b %d %H:%M:%S %Y", &tm);
        time_t t = mktime(&tm);
        if (t == -1) {
            return 0;
        }
        client_channel_print_threads(t_uuid, user_uuid, t, t_title, t_body);
    }
    return 0;
}

int list_reply_function (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 4) {
        if (!array[i + 1] || !array[i + 2] || !array[i + 3])
            return 0;
        char *thread = array[i];
        char *user = array[i + 1];
        char *time = array[i + 2];
        char *body = array[i + 3];
        struct tm tm;
        strptime(time, "%a %b %d %H:%M:%S %Y", &tm);
        time_t t = mktime(&tm);
        if (t == -1) {
            return 0;
        }
        client_thread_print_replies(thread, user, t, body);
    }
    return 0;
}
