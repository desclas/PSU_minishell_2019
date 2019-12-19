/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** access
*/

#include "minishell.h"

static int access_env(cmds_t *cmd, char *env, char **tmp)
{
    int res;

    for (size_t x = 5, y = 0; env[x] != '\0'; x = (env[y] == ':') ? y + 1 : y) {
        for (y = x; env[y] != '\0' && env[y] != ':'; y++);
        *tmp = my_append_str(my_strndup(&env[x], y - x),
            my_append_str(my_strdup("/"), my_strdup(cmd->cmd)));
        res = access(*tmp, F_OK | X_OK);
        if (res < 0 && errno != ENOENT) {
            free(*tmp);
            return (1);
        } else if (res == 0) {
            free(cmd->cmd);
            cmd->cmd = *tmp;
            return (0);
        } else
            free(*tmp);
    }
    return (1);
}

int access_it(cmds_t *cmd, char **env)
{
    size_t i;
    char *tmp;
    if (access(cmd->cmd, F_OK | X_OK) == 0)
        return (0);
    for (i = 0; env[i] != NULL; i++)
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            break;
    if (env[i] != NULL)
        return (access_env(cmd, env[i], &tmp));
    else {
        tmp = my_append_str(my_strdup("/bin/"), my_strdup(cmd->cmd));
        if (access(tmp, F_OK | X_OK) == 0) {
            free(cmd->cmd);
            cmd->cmd = tmp;
            return (0);
        } else {
            free(tmp);
            return (1);
        }
    }
}
