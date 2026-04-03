/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** description
*/

#include "../include/my.h"

void free_list(cmd_t *head)
{
    cmd_t *tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        if (tmp->args != NULL)
            free_tab(tmp->args);
        if (tmp->in_file != NULL)
            free(tmp->in_file);
        if (tmp->out_file != NULL)
            free(tmp->out_file);
        free(tmp);
    }
}
