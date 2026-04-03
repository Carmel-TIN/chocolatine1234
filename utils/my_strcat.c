/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include "../include/my.h"

char *my_strcat(const char *s1, const char *s2)
{
    int len1;
    int len2;
    char *new_str;

    if (!s1 || !s2)
        return NULL;
    len1 = my_strlen(s1);
    len2 = my_strlen(s2);
    new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
        return NULL;
    my_strcpy(new_str, s1);
    my_strcpy(new_str + len1, s2);
    return new_str;
}
