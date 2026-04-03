/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void free_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++) {
        free(tab[i]);
    }
    free(tab);
}

void rmlf(char *line)
{
    int i = 0;

    while (line[i]) {
        if (line[i] == '\n')
            line[i] = '\0';
        i++;
    }
}

void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n$> ", 4);
}

void execute_external(char **args, shell_t *shell)
{
    char *path = find_cmd_path(args[0], shell->env);

    if (path == NULL) {
        write(2, args[0], my_strlen(args[0]));
        write(2, ": Command not found.\n", 21);
        shell->last_sts = 1;
        return;
    }
    exec_cmd(path, args, shell);
    free(path);
}
