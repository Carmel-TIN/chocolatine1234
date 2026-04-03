/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include "../include/my.h"
#include <stdlib.h>

char *my_strdup(const char *str)
{
    int len;
    char *dup;

    len = my_strlen(str);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return NULL;
    my_strcpy(dup, str);
    return dup;
}
