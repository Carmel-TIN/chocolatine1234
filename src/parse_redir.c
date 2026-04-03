/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** description
*/

#include "../include/my.h"

static void shift_args(char **args, int i)
{
    free(args[i]);
    free(args[i + 1]);
    while (args[i + 2] != NULL) {
        args[i] = args[i + 2];
        i++;
    }
    args[i] = NULL;
    args[i + 1] = NULL;
}

static int redir_out(cmd_t *node, int i)
{
    if (my_strcmp(node->args[i], ">") != 0
        && my_strcmp(node->args[i], ">>") != 0)
        return (0);
    if (node->args[i + 1] == NULL) {
        write(2, "Missing name for redirect.\n", 27);
        return (-1);
    }
    if (node->out_file != NULL) {
        write(2, "Ambiguous output redirect.\n", 27);
        return (-1);
    }
    node->app_mode = (my_strcmp(node->args[i], ">>") == 0);
    node->out_file = my_strdup(node->args[i + 1]);
    shift_args(node->args, i);
    return (1);
}

static int redir_in(cmd_t *node, int i)
{
    if (my_strcmp(node->args[i], "<") != 0)
        return (0);
    if (node->args[i + 1] == NULL) {
        write(2, "Missing name for redirect.\n", 27);
        return (-1);
    }
    if (node->in_file != NULL) {
        write(2, "Ambiguous input redirect.\n", 26);
        return (-1);
    }
    node->in_file = my_strdup(node->args[i + 1]);
    shift_args(node->args, i);
    return (1);
}

static int clean_node(cmd_t *node)
{
    int i = 0;
    int res;

    while (node->args && node->args[i] != NULL) {
        res = redir_out(node, i);
        if (res == 0)
            res = redir_in(node, i);
        if (res == -1)
            return (84);
        if (res == 1)
            continue;
        i++;
    }
    return (0);
}

int clean_all_redirs(cmd_t *head, shell_t *shell)
{
    cmd_t *tmp;

    tmp = head;
    while (tmp != NULL) {
        if (clean_node(tmp) == 84) {
            shell->last_sts = 1;
            return (84);
        }
        tmp = tmp->next;
    }
    return (0);
}
