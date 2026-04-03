/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

char *the_path(char *dir, char *cmd)
{
    char *path = malloc(my_strlen(dir) + my_strlen(cmd) + 2);

    if (!path)
        return NULL;
    path = my_strcpy(path, dir);
    path = my_strcat(path, "/");
    path = my_strcat(path, cmd);
    return path;
}

char *get_env(char **env, char *key)
{
    int i = 0;
    int len = my_strlen(key);

    while (env[i]) {
        if (my_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return (&env[i][len + 1]);
        i++;
    }
    return NULL;
}

static char *verif_path(char *path_cpy, char *tok, char *cmd)
{
    char *full_path;

    while (tok) {
        full_path = the_path(tok, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path_cpy);
            return full_path;
        }
        free(full_path);
        tok = strtok(NULL, ":");
    }
    free(path_cpy);
    return (NULL);
}

char *find_cmd_path(char *cmd, char **env)
{
    char *p = get_env(env, "PATH");
    char *path_cpy = (p) ? my_strdup(p) : NULL;
    char *tok;

    if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.'))) {
        if (access(cmd, F_OK) == 0)
            return (my_strdup(cmd));
        return (NULL);
    }
    if (!path_cpy)
        return NULL;
    tok = strtok(path_cpy, ":");
    return (verif_path(path_cpy, tok, cmd));
}
