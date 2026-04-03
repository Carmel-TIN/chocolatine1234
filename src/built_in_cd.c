/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include "../include/my.h"

void upt_env_pwds(shell_t *shell, char *old_pwd)
{
    char new_pwd[2048];
    char *set_old[4] = {"setenv", "OLDPWD", old_pwd, NULL};
    char *set_new[4] = {"setenv", "PWD", NULL, NULL};

    if (getcwd(new_pwd, 2048) != NULL) {
        set_new[2] = new_pwd;
        builtin_setenv(set_old, shell);
        builtin_setenv(set_new, shell);
    }
}

static int c_args(char **args)
{
    int c = 0;

    for (int i = 1; args[i] != NULL; i++) {
        c++;
    }
    return c;
}

static int v_count(char **args, shell_t *shell)
{
    if (c_args(args) > 1) {
        write(2, "cd: Too many arguments.\n", 24);
        shell->last_sts = 1;
        return 1;
    }
    return 0;
}

static void print_nofod(char *dest, shell_t *shell)
{
    write(2, dest, my_strlen(dest));
    write(2, ": ", 2);
    write(2, strerror(errno), my_strlen(strerror(errno)));
    write(2, ".\n", 2);
    shell->last_sts = 1;
}

static void print_dest(char *dest)
{
    write(1, dest, my_strlen(dest));
    write(1, "\n", 1);
}

static char *get_cd_dest(char **args, char **env)
{
    char *dest = args[1];

    if (dest == NULL || my_strcmp(dest, "~") == 0)
        return (get_env(env, "HOME"));
    if (my_strcmp(dest, "-") == 0) {
        dest = get_env(env, "OLDPWD");
        if (!dest) {
            write(2, ": No such file or directory.\n", 29);
            return (NULL);
        }
        print_dest(dest);
    }
    return (dest);
}

int builtin_cd(char **args, shell_t *shell)
{
    char *dest;
    char cur_pwd[2048];

    if (v_count(args, shell) || !getcwd(cur_pwd, 2048))
        return (1);
    dest = get_cd_dest(args, shell->env);
    if (!dest)
        return (1);
    if (chdir(dest) == -1) {
        print_nofod(dest, shell);
        return (1);
    }
    upt_env_pwds(shell, cur_pwd);
    return (0);
}

/*int builtin_cd(char **args, shell_t *shell)
{
    char *dest;
    char cur_pwd[2048];

    if (v_count(args, shell))
        return 1;
    dest = args[1];
    if (getcwd(cur_pwd, 2048) == NULL)
        return (1);
    if (dest == NULL || my_strcmp(dest, "~") == 0)
        dest = get_env(shell->env, "HOME");
    if (my_strcmp(dest, "-") == 0) {
        dest = get_env(shell->env, "OLDPWD");
        if (!dest) {
            return (1);
        }
        print_dest(dest);
    }
    if (chdir(dest) == -1) {
        print_nofod(dest, shell);
        return (1);
    }
    upt_env_pwds(shell, cur_pwd);
    return (0);
}*/
