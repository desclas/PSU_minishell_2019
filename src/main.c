/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** main
*/

#include "minishell.h"

static void shell(char ***env)
{
    cmds_t *cmd = NULL;
    cmds_t *rep;

    while (1) {
        rep = NULL;
        if (cmd == NULL)
            cmd = get_prompt(*env);
        if (cmd != NULL)
            rep = exec_cmds(cmd, env);
        free_ucmd(&cmd, rep);
    }
}

int main(int av, char **ac, char **env)
{
    char **new_env;
    size_t i = 0;

    (void)av;
    (void)ac;
    for (i = 0; env[i] != NULL; i++);
    new_env = my_calloc(sizeof(char *) * (i + 1));
    for (size_t x = 0; x < i; x++)
        new_env[x] = my_strdup(env[x]);
    shell(&new_env);
    free_char_tab(new_env);
    return (0);
}
