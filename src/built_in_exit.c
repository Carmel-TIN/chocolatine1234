/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
    }
    return 1;
}

int builtin_exit(char **args, shell_t *shell)
{
    int status = shell->last_sts;

    if (isatty(0))
        write(1, "exit\n", 5);
    if (args[1] != NULL) {
        if (is_num(args[1])) {
            status = my_getnbr(args[1]);
        } else {
            write(1, "exit: Expression Syntax\n", 25);
            shell->last_sts = 1;
            return 1;
        }
    }
    shell->exit_shell = 1;
    shell->last_sts = status % 256;
    return 0;
}
