/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include "../include/my.h"

void my_putnbr_recursive(long n, int fd)
{
    char digit;

    if (n < 0) {
        write(fd, "-", 1);
        n = -n;
    }
    if (n > 9)
        my_putnbr_recursive(n / 10, fd);
    digit = (n % 10) + '0';
    write(fd, &digit, 1);
}
