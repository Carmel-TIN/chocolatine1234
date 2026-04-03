/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

int envlen(char **env)
{
    int i = 0;

    while (env && env[i])
        i++;
    return i;
}

char **copy_env(char **env)
{
    int len = envlen(env);
    char **env_cpy = malloc(sizeof(char *) * (len + 1));
    int i = 0;

    if (!env_cpy)
        return NULL;
    while (i < len) {
        env_cpy[i] = my_strdup(env[i]);
        i++;
    }
    env_cpy[i] = NULL;
    return env_cpy;
}
