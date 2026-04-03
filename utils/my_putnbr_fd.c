/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include "../include/my.h"

void my_putnbr_fd(long n, int fd)
{
    if (n == 0) {
        write(fd, "0", 1);
        return;
    }
    my_putnbr_recursive(n, fd);
}
