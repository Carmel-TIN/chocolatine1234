/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void verif_sigmess(int sig)
{
    char *errmsg;

    if (sig == SIGSEGV) {
        errmsg = strsignal(sig);
        write(2, errmsg, my_strlen(errmsg));
    } else if (sig == SIGFPE)
        write(2, "Floating exception", 18);
    else
        write(2, strsignal(sig), my_strlen(strsignal(sig)));
}

void handle_sig(int status, shell_t *shell)
{
    int sig;

    if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        verif_sigmess(sig);
        if (WCOREDUMP(status))
            write(2, " (core dumped)\n", 15);
        else {
            write(2, "\n", 2);
            shell->last_sts = 1;
            return;
        }
        shell->last_sts = 128 + sig;
    } else if (WIFEXITED(status)) {
        shell->last_sts = WEXITSTATUS(status);
    }
}

void wait_all_children(cmd_t *head, shell_t *shell)
{
    cmd_t *tmp;
    int status;

    tmp = head;
    while (tmp != NULL) {
        if (tmp->pid > 0) {
            waitpid(tmp->pid, &status, 0);
            handle_sig(status, shell);
        }
        tmp = tmp->next;
    }
}
