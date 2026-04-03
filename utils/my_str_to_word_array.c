/*
** EPITECH PROJECT, 2025
** str_to_word_array
** File description:
** description
*/

#include <stdlib.h>

static int is_delim(char c, const char *delim)
{
    for (int i = 0; delim[i]; i++) {
        if (c == delim[i])
            return 1;
    }
    return 0;
}

char *my_strndup(char const *src, int n)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * (n + 1));

    if (dest == NULL)
        return NULL;
    while (i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int count_words(char const *str, char const *delim)
{
    int words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_delim(str[i], delim) && (i == 0 || is_delim(str[i - 1], delim)))
            words++;
    }
    return words;
}

char **str_to_word_array(char const *str, char const *delim)
{
    int st = 0;
    int nb_words = count_words(str, delim);
    char **tab = malloc(sizeof(char *) * (nb_words + 1));
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_delim(str[i], delim)) {
            continue;
        }
        st = i;
        while (str[i] != '\0' && !is_delim(str[i], delim))
            i++;
        tab[j] = my_strndup(&str[st], i - st);
        j++;
        if (str[i] == '\0')
            break;
    }
    tab[j] = NULL;
    return tab;
}
