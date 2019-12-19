/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** execute
*/

#include "minishell.h"

static void child(cmds_t *list, char ***env)
{
    pid_t pid = fork();
    if (pid == 0) {
        if (list->rred != NULL && list->rred[0] == '|')
        {
            close(list->prev->pfd[1]);
            dup2(list->prev->pfd[0], STDIN_FILENO);
            close(list->prev->pfd[0]);
        } else
            read_red(list, *env);
        if (list->wred != NULL && list->wred[0] == '|') {
            close(list->pfd[0]);
            dup2(list->pfd[1], STDOUT_FILENO);
            close(list->pfd[1]);
        } else
            write_red(list, *env);
        (access_it(list, *env)) ? exit_error(NULL, NULL, list->cmd) : 0;
        execve(list->cmd, list->args, *env);
        exit_error(NULL, NULL, "execve");
    } else
        list->pid = pid;
    dprintf(2, "pid of \"%s\" is %d\n", list->cmd, list->pid);
}

static void exec_rec(cmds_t *list, char ***env)
{
    if (list->next != NULL && list->next->next != NULL &&
            list->next->next->wred != NULL && list->next->next->wred[0] == '|'){
        close(list->next->next->pfd[0]);
        close(list->next->next->pfd[1]);
    }
    if (list->rred != NULL && list->rred[0] == '|')
        pipe(list->prev->pfd);
    if (is_builtin(list, env));
    else
        child(list, env);
    (list->rred != NULL && list->rred[0] == '|') ? exec_rec(list->prev, env) :0;
}
/*
static void wait_it(cmds_t * list)
{
    int st;

    if ((list->wred == NULL || (list->wred != NULL && list->wred[0] != '|')) &&
            list->pid != 0) {
        dprintf(2, "waiting only \"%s\"   pid is %d\n", list->cmd, list->pid);
        wait(&st);
        (WIFSIGNALED(st)) ? strsignal(WTERMSIG(st)) : 0;
    } else {
        for (dprintf(2, "multiple wait\n"); (list->wred != NULL && list->wred[0] == '|') || (list->rred != NULL && list->rred[0] == '|'); list = list->next, st = 0) {
            dprintf(2, "waiting for \"%s\"  pid is %d\n", list->cmd, list->pid);
            (list->pid != 0) ? waitpid(list->pid, &st, 0) : 0;
            dprintf(2, "\"%s\" has stoped\n", list->cmd);
            (WIFSIGNALED(st)) ? strsignal(WTERMSIG(st)) : 0;
        }
    }
}*/

cmds_t *exec_cmds(cmds_t *list, char ***env)
{
    cmds_t *tmp = list;
    for (; tmp != NULL && tmp->wred && !my_strncmp(tmp->wred, "|", 1);
         tmp = tmp->next);
    if (tmp != list)
        exec_rec(tmp, env);
    else {
        if (is_builtin(list, env));
        else
            child(list, env);
    }
    wait(NULL);
    for (size_t i = 0; list->wred != NULL && list->wred[0] == '|' && i < 2;
            i++, list = list->next) {
        close(list->pfd[0]);
        close(list->pfd[1]);
    }
    return (tmp);
}
