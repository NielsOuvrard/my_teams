/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myteams-niels.ouvrard
** File description:
** my_str_to_word_array
*/

#include "my.h"

void print_map(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        printf("%s\n", map[i]);
}

int is_alpha(char c)
{
    if (c >= 33 && c <= 127)
        return 0;
    else
        return 1;
}

int is_alphabet(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 0;
    else if (c >= 'a' && c <= 'z')
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

char **my_str_to_word_array(char *str)
{
    int word = 0, i = 0;
    char **array = NULL;
    str[strlen(str)] = '\0';
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_alpha(str[i]) == 0 && (str[i + 1] == '\0' ||
is_condition(str[i + 1]) == 1))
            word++;
    }
    array = malloc(sizeof(char *) * (word + 1));
    array[word] = NULL;
    for (int size = 0, j = 0, l = 0, aux = 0; i < word; i++) {
        for (; is_condition(str[j]) == 1; j++, l++);
        for (; is_condition(str[j]) != 1; j++, size++);
        array[i] = malloc(sizeof(char) * size + 1);
        for (aux = 0; is_condition(str[l]) != 1; l++, aux++)
            array[i][aux] = str[l];
        array[i][aux] = '\0';
        size = 0;
    }
    return array;
}
