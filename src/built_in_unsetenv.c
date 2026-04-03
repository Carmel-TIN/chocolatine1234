/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void rm_var(char *key, shell_t *shell)
{
    int idx = find_env_idx(shell->env, key);

    if (idx == -1)
        return;
    free(shell->env[idx]);
    while (shell->env[idx] != NULL) {
        shell->env[idx] = shell->env[idx + 1];
        idx++;
    }
}

int builtin_unsetenv(char **args, shell_t *shell)
{
    if (!args[1]) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        shell->last_sts = 1;
        return 1;
    }
    for (int i = 1; args[i]; i++) {
        rm_var(args[i], shell);
    }
    return 0;
}
