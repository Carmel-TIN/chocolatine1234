/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void disp_cwd(shell_t *shell)
{
    char cwd[2048];
    char *home = get_env(shell->env, "HOME");
    int len;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return;
    write(1, "\033[1;34m", 7);
    if (home && my_strncmp(cwd, home, my_strlen(home)) == 0) {
        write(1, "~", 1);
        len = my_strlen(cwd + my_strlen(home));
        write(1, cwd + my_strlen(home), len);
    } else {
        write(1, cwd, my_strlen(cwd));
    }
    write(1, "\033[0m", 4);
}

void disp_prompt(shell_t *shell)
{
    char *user = get_env(shell->env, "USER");

    if (!isatty(0))
        return;
    if (user) {
        write(1, "\033[1;32m", 7);
        write(1, user, my_strlen(user));
        write(1, "\033[0m", 4);
    }
    write(1, ":", 1);
    disp_cwd(shell);
    write(1, "\033[1;31m$>\033[0m ", 14);
}
