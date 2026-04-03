/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** description
*/

#include "../include/my.h"

char *rm_spaces(char *str)
{
    int start = 0;
    int end;

    if (str == NULL)
        return (NULL);
    while (str[start] == ' ' || str[start] == '\t')
        start++;
    if (str[start] == '\0')
        return (&str[start]);
    end = strlen(str) - 1;
    while (end > start && (str[end] == ' ' || str[end] == '\t'))
        end--;
    str[end + 1] = '\0';
    return (&str[start]);
}
