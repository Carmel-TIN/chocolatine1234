/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** description
*/

#include "../include/my.h"

static void setup_pipeline(int in_fd, int out_fd)
{
    if (in_fd != STDIN_FILENO) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO) {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

static int apply_files(cmd_t *node)
{
    int fd;

    if (node->out_file) {
        fd = open(node->out_file, O_WRONLY | O_CREAT |
            (node->app_mode ? O_APPEND : O_TRUNC), 0644);
        if (fd == -1)
            return -1;
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    if (node->in_file) {
        fd = open(node->in_file, O_RDONLY);
        if (fd == -1)
            return -1;
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    return (0);
}

static void child_pipe_exec(cmd_t *node, shell_t *shell, int in_fd, int p_fd[2])
{
    int out_fd = (node->next != NULL) ? p_fd[1] : STDOUT_FILENO;

    setup_pipeline(in_fd, out_fd);
    if (node->next != NULL)
        close(p_fd[0]);
    if (apply_files(node) == -1) {
        perror(node->out_file ? node->out_file : node->in_file);
        exit(1);
    }
    if (check_builtins(node->args, shell))
        exit(shell->last_sts);
    execute_external(node->args, shell);
    exit(shell->last_sts);
}

void execute_pipeline(cmd_t *head, shell_t *shell)
{
    int p_fd[2];
    int prev_fd = STDIN_FILENO;
    cmd_t *tmp = head;

    while (tmp != NULL) {
        if (tmp->next != NULL)
            pipe(p_fd);
        tmp->pid = fork();
        if (tmp->pid == 0)
            child_pipe_exec(tmp, shell, prev_fd, p_fd);
        if (prev_fd != STDIN_FILENO)
            close(prev_fd);
        if (tmp->next != NULL) {
            prev_fd = p_fd[0];
            close(p_fd[1]);
        }
        tmp = tmp->next;
    }
    wait_all_children(head, shell);
}
