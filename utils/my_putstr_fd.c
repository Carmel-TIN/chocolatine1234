/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include "../include/my.h"
#include <unistd.h>

void my_putstr_fd(const char *str, int fd)
{
    int len;

    if (!str)
        return;
    len = my_strlen(str);
    write(fd, str, len);
}
