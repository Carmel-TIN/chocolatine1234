/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void execute_command(cmd_t *list, shell_t *shell)
{
    if (list->next == NULL && check_builtins(list->args, shell))
        return;
    execute_pipeline(list, shell);
}

void process_pipeline(char *segment, shell_t *shell)
{
    cmd_t *list;

    list = parse_pipe(segment, shell);
    if (list == NULL)
        return;
    if (clean_all_redirs(list, shell) != 84) {
        execute_command(list, shell);
    }
    free_list(list);
}

void handle_semicolons(char *line, shell_t *shell)
{
    char **segs;
    int i;

    segs = str_to_word_array(line, ";");
    if (segs == NULL)
        return;
    i = 0;
    while (segs[i] != NULL) {
        process_pipeline(segs[i], shell);
        i++;
    }
    free_tab(segs);
}

int main(int ac, char **av, char **env)
{
    char *line = NULL;
    size_t len = 0;
    shell_t shell;

    (void)av;
    if (ac != 1)
        return 84;
    shell.env = copy_env(env);
    shell.exit_shell = 0;
    signal(SIGINT, handle_sigint);
    while (shell.exit_shell == 0) {
        disp_prompt(&shell);
        if (getline(&line, &len, stdin) == -1)
            break;
        rmlf(line);
        handle_semicolons(line, &shell);
    }
    free(line);
    free_tab(shell.env);
    return (shell.last_sts);
}
