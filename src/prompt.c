/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** prompt
*/

#include "minishell.h"

static int put_red_npipe(char *line, cmds_t *new, int *i, int *x)
{
    for (*x = *i; (IS_REDIREC(line[*i]) || line[*i] == 32) && line[*i] !=0;
        *i += 1);
    for (; line[*i] != ' ' && line[*i] != 0; *i += 1);
    if (((line[*x] == '<') ? new->rred : new->wred) != NULL)
        return (write(2, "Ambiguous input redirect.\n", 26) * (-1));
    (line[*x] == '<') ? (new->rred = my_strndup(line, *i - *x)) :
        (new->wred = my_strndup(line, *i - *x));
    return (0);
}

static int put_redirections(char *line, cmds_t *new)
{
    static char p = 0;
    int i = 0;
    int x;
    for (i = 0; line[i] != '\0' && !IS_SREDIREC(line[i]); i++);
    if (p == 1) {
        new->rred = my_strdup("|");
        p ^= 1;
    }
    if (IS_REDIREC(line[i]) && line[i] !='|' && put_red_npipe(line,new,&i,&x)<0)
        return (-1);
    if (line[i] == '|') {
        if (new->wred != NULL)
            return (write(2, "Ambiguous output redirect.\n", 27) * (-1));
        new->wred = my_strdup("|") + (i++ * 0);
        p ^= 1;
    }
    for (; (line[i] == ' ' || IS_SEMI(line[i])) && line[i] != '\0'; i++);
    if (IS_REDIREC(line[i]))
        return (((x = put_redirections(&line[i], new)) < 0) ? -1 : i + x);
    return (i);
}

static cmds_t *get_cmd(char *line)
{
    cmds_t *res = NULL;
    cmds_t *new = NULL;

    if (IS_REDIREC(line[0]))
        return ((void *)(write(2, "Invalid null command.\n", 23) * 0));
    if (check_quote(line))
        return (NULL);
    for (int i = 0, x = 0, err; line[i]!=0; res = add_dlist(res,new), i+=err) {
        new = my_calloc(sizeof(*new));
        for (x = i; line[i] != ' ' && line[i] != '\0'; i++);
        new->cmd = my_strndup(&line[x], i - x);
        for (; line[i] != '\0' && !IS_SREDIREC(line[i]); i++)
            i += pass_quote(&line[i]);
        i = (line[i] == ' ') ? i - 1 : i;
        new->args = my_nstr_to_wordtab(&line[x], i - x);
        err = put_redirections(&line[i], new);
        if (err < 0)
            return (((cmds_t *)(free_fcmds(res, new) * 0)));
    }
    return (res);
}

cmds_t *get_prompt(char **env)
{
    cmds_t *res = NULL;
    char *line = NULL;
    size_t s = 0;

    my_putnstr("> ", 2);
    if (getline(&line, &s, stdin) < 0)
        exit_error(NULL, env, "an error occured in getline");
    my_epurstr(line);
    line[my_strlen(line) - 1] = '\0';
    if (line[0] == '\0') {
        free(line);
        return (NULL);
    }
    res = get_cmd(line);
    free(line);
    return (res);
}
