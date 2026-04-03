/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

int my_strlen(const char *str)
{
    int x = 0;

    while (str[x] != '\0')
        x++;
    return x;
}
