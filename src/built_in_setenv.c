/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

static int is_alnum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || (c == '_'))
        return 1;
    return 0;
}

static int valid_var_nm(char *str)
{
    if (!((str[0] >= 'a' && str[0] <= 'z') ||
            (str[0] >= 'A' && str[0] <= 'Z'))) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return 0;
    }
    for (int i = 0; str[i]; i++) {
        if (!is_alnum(str[i])) {
            write(2, "setenv: Variable name must contain ", 35);
            write(2, "alphanumeric characters.\n", 25);
            return 0;
        }
    }
    return 1;
}

static int count_args(char **args)
{
    int c = 0;

    for (int i = 1; args[i] != NULL; i++) {
        c++;
    }
    return c;
}

static int vef_count(char **args, shell_t *shell)
{
    if (count_args(args) > 2) {
        write(2, "setenv: Too many arguments.\n", 28);
        shell->last_sts = 1;
        return 1;
    }
    return 0;
}

int find_env_idx(char **env, char *key)
{
    int i = 0;
    int len = my_strlen(key);

    while (env[i]) {
        if (my_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
            return i;
        i++;
    }
    return (-1);
}

char **add_to_env(char **env, char *new_var)
{
    int len = envlen(env);
    char **new_env = malloc(sizeof(char *) * (len + 2));
    int i = 0;

    if (!new_env)
        return (env);
    while (i < len) {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = new_var;
    new_env[i + 1] = NULL;
    free(env);
    return new_env;
}

char *create_env_var(char *key, char *value)
{
    int k_len = my_strlen(key);
    int v_len = (value) ? my_strlen(value) : 0;
    char *new_var = malloc(sizeof(char) * (k_len + v_len + 2));

    if (!new_var)
        return NULL;
    my_strcpy(new_var, key);
    new_var[k_len] = '=';
    if (value)
        my_strcpy(new_var + k_len + 1, value);
    else
        new_var[k_len + 1] = '\0';
    return new_var;
}

int builtin_setenv(char **args, shell_t *shell)
{
    int idx = 0;
    char *new_var = NULL;

    if (!args[1])
        return (builtin_env(shell));
    if (vef_count(args, shell))
        return 1;
    if (!valid_var_nm(args[1])) {
        shell->last_sts = 1;
        return 1;
    }
    new_var = create_env_var(args[1], args[2]);
    idx = find_env_idx(shell->env, args[1]);
    if (idx != -1) {
        free(shell->env[idx]);
        shell->env[idx] = new_var;
    } else
        shell->env = add_to_env(shell->env, new_var);
    return 0;
}
