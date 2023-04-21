/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** command_1
*/

#include "my_client.h"

char *strptime(const char *s, const char *format, struct tm *tm);

int messages_function       (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 3) {
        if (!array[i + 1] || !array[i + 2])
            return 0;
        char *sender = array[i];
        char *message = array[i + 1];
        char *date = array[i + 2];
        struct tm tm;
        strptime(date, "%a %b %d %H:%M:%S %Y", &tm);
        time_t t = mktime(&tm);
        if (t == -1) {
            return 0;
        }
        client_private_message_print_messages(sender, t, message);
    }
    return 0;
}

int subscribe_function      (client *cli, char **array)
{
    if (array[1] && array[2])
        client_print_subscribed(array[1], array[2]);
    return 0;
}

int subscribed_function     (client *cli, char **array)
{
    for (int i = 1; array[i] != NULL; i += 3) {
        if (!array[i + 1] || !array[i + 2])
            return 0;
        client_print_users(array[i], array[i + 1], atoi(array[i + 2]));
    }
    return 0;
}

int unsubscribe_function    (client *cli, char **array)
{
    if (array[1] && array[2])
        client_print_unsubscribed(array[1], array[2]);
    return 0;
}

int use_function            (client *cli, char **array)
{
    return 0;
}
