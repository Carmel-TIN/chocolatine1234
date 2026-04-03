/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

char *my_strcpy(char *dest, const char *src)
{
    int x = 0;

    while (src[x] != '\0') {
        dest[x] = src[x];
        x++;
    }
    dest[x] = '\0';
    return dest;
}
