/*
** EPITECH PROJECT, 2025
** projet
** File description:
** description
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <errno.h>
    #include <signal.h>
    #include <fcntl.h>

typedef struct shell {
    char **env;
    int last_sts;
    int exit_shell;
} shell_t;

typedef struct cmd_s {
    char **args;
    char *in_file;
    char *out_file;
    int app_mode;
    int fd[2];
    pid_t pid;
    struct cmd_s *next;
} cmd_t;

void my_putnbr_fd(long n, int fd);
void my_putnbr_recursive(long n, int fd);
void my_putstr_fd(const char *str, int fd);
char **str_to_word_array(char const *str, char const *delim);
char *my_strcat(const char *s1, const char *s2);
int my_strcmp(const char *s1, const char *s2);
char *my_strcpy(char *dest, const char *src);
char *my_strdup(const char *str);
int my_strlen(const char *str);
char *my_strndup(char const *src, int n);
int my_strncmp(const char *s1, const char *s2, size_t n);
int my_getnbr(char const *str);
char **copy_env(char **env);
int builtin_env(shell_t *shell);
char *find_cmd_path(char *cmd, char **env);
char **copy_env(char **env);
int exec_cmd(char *path, char **ar, shell_t *shell);
void handle_sig(int status, shell_t *shell);
char *get_env(char **env, char *key);
int builtin_cd(char **args, shell_t *shell);
void free_tab(char **tab);
int envlen(char **env);
int builtin_setenv(char **args, shell_t *shell);
int find_env_idx(char **env, char *key);
int builtin_unsetenv(char **args, shell_t *shell);
int builtin_exit(char **args, shell_t *shell);
int check_builtins(char **args, shell_t *shell);
void disp_prompt(shell_t *shell);
void rmlf(char *line);
void handle_sigint(int sig);
void execute_external(char **args, shell_t *shell);
char *rm_spaces(char *str);
cmd_t *parse_pipe(char *seg, shell_t *shell);
int clean_all_redirs(cmd_t *head, shell_t *shell);
void wait_and_set_status(pid_t pid, shell_t *shell);
void execute_pipeline(cmd_t *head, shell_t *shell);
void wait_all_children(cmd_t *head, shell_t *shell);
void wait_and_set_status(pid_t pid, shell_t *shell);
void free_list(cmd_t *head);

#endif
