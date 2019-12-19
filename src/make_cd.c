/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** make_cd
*/

#include "minishell.h"

static char make_cd_back(cmds_t *list, char ***env)
{
    size_t i;

    for (i = 0; env[0][i] != NULL &&my_strncmp(env[0][i],"OLD_PWD=",8);i++);
    if (env[0][i] == NULL) {
        my_puterr(": No such file or directory.\n");
        return (-1);
    } else {
        free(list->args[1]);
        list->args[1] = my_strdup(env[0][i] + 8);
    }
    return (0);
}

static void make_cd_home(cmds_t *list, char ***env)
{
    char *tmp;
    size_t i;

    if (list->args[1] != NULL && list->args[1][0] =='~') {
        for (i = 0; env[0][i] != NULL && my_strncmp(env[0][i], "HOME=", 6);i++);
        if (env[0][i] != NULL) {
            tmp = list->args[1];
            list->args[1] = my_append_str(my_strdup(env[0][i] + 5),
                my_strdup(list->args[1] + 1));
            free(tmp);
        }
    } else {
        for (i = 0; env[0][i] != NULL && my_strncmp(env[0][i], "HOME=", 6);i++);
        if (env[0][i] != NULL) {
            tmp = my_strdup(env[0][i] + 5);
            (chdir(tmp) < 0) ? perror(tmp) : set_env(env, "PWD", tmp);
            free(tmp);
        } else
            my_puterr("cd: No home directory.\n");
    }
}

void make_cd(cmds_t *list, char ***env)
{
    char *tmp;

    if (list->args[1] != NULL && list->args[2] != NULL) {
        my_puterr("cd: Too many arguments.\n");
        return;
    } else if (list->args[1] != NULL && !my_strcmp(list->args[1], "-") &&
        make_cd_back(list, env) == -1)
        return;
    tmp = getcwd(NULL, 0);
    if (tmp == NULL)
        return;
    set_env(env, "OLD_PWD", tmp);
    free(tmp);
    if ((list->args[1] != NULL && list->args[1][0]=='~') || list->args[1]==NULL)
        make_cd_home(list, env);
    else
        (chdir(list->args[1]) < 0) ? perror(list->args[1]) :
            set_env(env, "PWD", list->args[1]);
}
