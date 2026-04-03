/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

static cmd_t *init_node(char *str)
{
    cmd_t *node = malloc(sizeof(cmd_t));

    if (node == NULL)
        return NULL;
    node->args = str_to_word_array(str, " \t");
    node->in_file = NULL;
    node->out_file = NULL;
    node->app_mode = 0;
    node->next = NULL;
    return node;
}

static int is_invalid_pipe(char *str)
{
    char *clean_str = rm_spaces(str);

    if (clean_str[0] == '\0') {
        write(2, "Invalid null command.\n", 22);
        return 1;
    }
    return 0;
}

static void add_to_list(cmd_t **head, cmd_t *new)
{
    cmd_t *tmp = NULL;

    if (*head == NULL) {
        *head = new;
        return;
    }
    tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

cmd_t *parse_pipe(char *seg, shell_t *shell)
{
    char **tab = str_to_word_array(seg, "|");
    cmd_t *head = NULL;

    if (tab == NULL)
        return NULL;
    for (int i = 0; tab[i] != NULL; i++) {
        if (is_invalid_pipe(tab[i])) {
            shell->last_sts = 1;
            return NULL;
        }
        add_to_list(&head, init_node(tab[i]));
    }
    free_tab(tab);
    return head;
}
