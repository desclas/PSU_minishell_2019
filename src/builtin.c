/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** builtin
*/

#include "minishell.h"

static void preset_builtin(cmds_t *list, char **env)
{
    if (list->wred != NULL && list->wred[0] == '|') {
        close(list->pfd[0]);
        dup2(list->pfd[1], 1);
        close(list->pfd[1]);
    } else
        write_red(list, env);
    if (list->rred != NULL && list->rred[0] == '|') {
        close(list->prev->pfd[1]);
        dup2(list->prev->pfd[0], 0);
        close(list->prev->pfd[0]);
    } else
        read_red(list, env);
}

static void offset_builtin(int se, int ss)
{
    dup2(se, 0);
    dup2(ss, 1);
    close(se);
    close(ss);
}

void print_env(cmds_t *list, char ***env)
{
    int se = dup(STDIN_FILENO);
    int ss = dup(STDOUT_FILENO);

    preset_builtin(list, *env);
    for (size_t i = 0; env[0][i] != NULL; i++) {
        my_putstr(env[0][i]);
        my_putchar('\n');
    }
    offset_builtin(se, ss);
}


int is_builtin(cmds_t *list, char ***env)
{
    char tab[4][10] = {"cd", "env", "setenv", "unsetenv"};
    void (*ptr[4])(cmds_t *, char ***) = {&make_cd, &print_env, &preset_env,
        &unset_env};
    int ret = 0;

    if (!my_strcmp(list->cmd, "exit"))
        exit_error(list, *env, NULL);
    for (size_t i = 0; i < 4; i++)
        if (!strcmp(tab[i], list->cmd)) {
            ptr[i](list, env);
            ret = 1;
            break;
        }
    return (ret);
}
