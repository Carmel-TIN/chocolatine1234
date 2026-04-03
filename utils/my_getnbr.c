/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#include <stdio.h>

static long ext_nbr(char const *str, int x)
{
    long res = 0;

    while (str[x] != '\0') {
        if (str[x] >= '0' && str[x] <= '9')
            res = res * 10 + (str[x] - '0');
        else
            break;
        x++;
    }
    return res;
}

int my_getnbr(char const *str)
{
    int x = 0;
    long res = 0;
    int my_sign = 1;

    while (str[x] != '\0' && (str[x] == '+' || str[x] == '-')) {
        if (str[x] == '-')
            my_sign *= -1;
        x++;
    }
    res = ext_nbr(str, x);
    if (res > 2147483647)
        return 0;
    if (my_sign == -1) {
        if (my_sign * res < -2147483648)
            return 0;
        return (res * my_sign);
    }
    return (int)res;
}
