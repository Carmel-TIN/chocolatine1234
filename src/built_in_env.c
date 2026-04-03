/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

int builtin_env(shell_t *shell)
{
    int i = 0;

    if (!shell->env)
        return 1;
    while (shell->env[i]) {
        write(1, shell->env[i], my_strlen(shell->env[i]));
        write(1, "\n", 1);
        i++;
    }
    return 0;
}
