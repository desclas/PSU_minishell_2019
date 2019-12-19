/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** builtin_env
*/

#include "minishell.h"

static void delete_on_char_tab(char **tab)
{
    for (size_t i = 0; tab[i] != NULL; i++)
        tab[i] = tab[i + 1];
}

void set_env(char ***env, char *name, char *value)
{
    size_t i;
    char *tmp;

    for (i = 0; name[i] != 0; i++)
        if (!IS_ALPHANUM(name[i])) {
            my_puterr("setenv: Variable name must contain alphanumeric "
                "characters.\n");
            return;
        }
    tmp = my_append_str(my_strdup(name), my_strdup("="));
    for (i=0; env[0][i] !=NULL && my_strncmp(tmp,env[0][i],my_strlen(tmp));i++);
    if (env[0][i] == NULL)
        *env = my_append_char_tab(*env, my_append_str(tmp, my_strdup(value)));
    else {
        free(env[0][i]);
        env[0][i] = my_append_str(tmp, my_strdup(value));
    }
}

void preset_env(cmds_t *list, char ***env)
{
    if (list->args[1] == NULL)
        print_env(list, env);
    else if (list->args[1] != NULL && list->args[2] != NULL &&
        list->args[3] != NULL)
        my_puterr("setenv: Too many arguments.\n");
    else
        set_env(env, list->args[1], list->args[2]);
}

void unset_env(cmds_t *list, char ***env)
{
    char *tmp;
    char **en = *env;

    if (list->args[1] == NULL) {
        my_puterr("unsetenv: Too few arguments.\n");
        return;
    }
    for (size_t i = 1, x; list->args[i] != NULL; i++) {
        tmp = my_append_str(my_strdup(list->args[i]), my_strdup("="));
        for (x = 0; en[x] != NULL && my_strncmp(tmp,en[x],my_strlen(tmp)); x++);
        if (en[x] != NULL)
            delete_on_char_tab(&en[x]);
        free(tmp);
    }
}
