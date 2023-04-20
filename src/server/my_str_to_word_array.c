/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** my_str_to_word_array
*/

#include "my_server.h"

int is_alpha(char c)
{
    if (c >= 33 && c <= 127)
        return 0;
    else
        return 1;
}

int is_condition(char c)
{
    if (c == '\t')
        return 1;
    if (c == ' ')
        return 1;
    if (c == '\0')
        return 1;
    if (c == '\n')
        return 1;
    if (c == ':')
        return 1;
    return 0;
}

char* substring(char* str, char start, char end) {
    char* substr = NULL;
    char* start_ptr = strchr(str, start) - 1;
    char* end_ptr = strchr(str, end);
    if (start_ptr && end_ptr && end_ptr > start_ptr) {
        size_t length = end_ptr - start_ptr - 1;
        substr = (char*) malloc(length + 1);
        memcpy(substr, start_ptr + 1, length);
        substr[length] = '\0';
    }

    return substr;
}

char *parse_by_quote(char *str)
{
    char *new = malloc(sizeof(char) * (strlen(str) + 2));
    int in_quote = 0, i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            in_quote += 1;
        if (in_quote == 2)
            break;
        new[i] = str[i];
    }
    new[i] = '\"';
    new[i + 1] = '\0';
    if (in_quote != 2) {
        free(new);
        return NULL;
    }
    return new;
}

char **my_str_to_word_array(char *str)
{
    int word = 0, i = 0, in_quote = 0;
    char **array = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"')
            in_quote = (in_quote == 0) ? 1 : 0;
        if (is_alpha(str[i]) == 0 && (str[i + 1] == '\0' ||
is_condition(str[i + 1]) == 1) && in_quote == 0)
            word++;
    }
    array = malloc(sizeof(char *) * (word + 1));
    array[word] = NULL;
    if (word == 1) {
        array[0] = strdup(str); return array;
    }
    array[0] = substring(str, '/', ' '); str = str + strlen(array[0]) + 1;
    char *tmp; i = 1;
    while ((tmp = parse_by_quote(str)) != NULL) {
        array[i] = strdup(tmp);
        str = str + strlen(array[i]) + 1; i++;
    } return array;
}
