/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

int my_strcmp(const char *s1, const char *s2)
{
    int x = 0;

    while (s1[x] != '\0' && s2[x] != '\0') {
        if (s1[x] != s2[x])
            return ((unsigned char)s1[x] - (unsigned char)s2[x]);
        x++;
    }
    return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}
