/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

static int check_exit(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "exit") == 0) {
        builtin_exit(args, shell);
        return 1;
    }
    return 0;
}

int check_builtins(char **args, shell_t *shell)
{
    if (my_strcmp(args[0], "env") == 0) {
        builtin_env(shell);
        return 1;
    }
    if (my_strcmp(args[0], "cd") == 0) {
        builtin_cd(args, shell);
        return 1;
    }
    if (my_strcmp(args[0], "setenv") == 0) {
        builtin_setenv(args, shell);
        return 1;
    }
    if (my_strcmp(args[0], "unsetenv") == 0) {
        builtin_unsetenv(args, shell);
        return 1;
    }
    if (check_exit(args, shell) == 1)
        return 1;
    return 0;
}

static void child_proc(char *path, char **ar, char **env)
{
    int ret = 0;

    if (path == NULL)
        exit(1);
    ret = execve(path, ar, env);
    if (ret == -1) {
        if (errno == ENOEXEC) {
            write(2, ar[0], my_strlen(ar[0]));
            write(2, ": Exec format error. ", 21);
            write(2, "Wrong Architecture.\n", 20);
        } else {
            write(2, ar[0], my_strlen(ar[0]));
            write(2, ": ", 2);
            write(2, strerror(errno), my_strlen(strerror(errno)));
            write(2, ".\n", 2);
        }
        free(path);
        exit(1);
    }
    free(path);
}

int exec_cmd(char *path, char **ar, shell_t *shell)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        child_proc(path, ar, shell->env);
    } else {
        waitpid(pid, &status, 0);
        handle_sig(status, shell);
    }
    return 0;
}
