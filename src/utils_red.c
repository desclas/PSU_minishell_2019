/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** utils_red
*/

#include "minishell.h"

void exit_error(cmds_t *list, char **env, char *msg)
{
    (msg != NULL) ? perror(msg) : 0;
    free_char_tab(env);
    for (size_t i = 0; list != NULL && list->wred != NULL &&
        list->wred[0] == '|' && i < 2; i++, list = list->next) {
        close(list->pfd[0]);
        close(list->pfd[1]);
    }
    for (; list != NULL && list->prev != NULL; list = list->prev);
    free_fcmds(list, NULL);
    exit((msg == NULL) ? 0 : 84);
}

static void read_red_pipe(cmds_t *list)
{
    char *tmp = NULL;
    char *gnl = NULL;
    size_t st = 0;
    int pfd[2];

    tmp = my_calloc(sizeof(char));
    write(1, "? ", 2);
    for (; getline(&gnl, &st, stdin) > 0 && my_strncmp(gnl, list->rred + 3,
        my_strlen(gnl) - 1); tmp = my_append_str(tmp, gnl), gnl = NULL,st=0)
        write(1, "? ", 2);
    free(gnl);
    pipe(pfd);
    dup2(pfd[0], 0);
    write(pfd[1], tmp, my_strlen(tmp));
    close(pfd[1]);
    close(pfd[0]);
    free(tmp);
}

void read_red(cmds_t *list, char **env)
{
    int fd;

    (void)env;
    if (list->rred != NULL && list->rred[1] == ' ') {
        fd = open(list->rred + 2, O_RDONLY);
        if (fd < 0)
            (fd < 0) ? exit_error(NULL, NULL, list->rred + 2) : perror(list->rred);
        else {
            dup2(fd, 0);
            close(fd);
        }
    } else if (list->rred != NULL) {
        read_red_pipe(list);
    }
}

void write_red(cmds_t *list, char **env)
{
    int tfd;
    char *tmp;

    (void)env;
    if (list->wred == NULL)
        return;
    for (tmp = list->wred; *tmp == '>' || *tmp == ' '; tmp++);
    tfd = open(tmp, ((list->wred[1] == '>') ? O_WRONLY | O_APPEND | O_CREAT :
        O_WRONLY | O_CREAT), 00666);
    if (tfd < 0)
        tfd = open(tmp, ((list->wred[1] == '>') ? O_WRONLY |O_APPEND:O_WRONLY));
    if (tfd < 0)
        (tfd < 0) ? exit_error(NULL, NULL, tmp) : perror(tmp);
    else {
        dup2(tfd, 1);
        close(tfd);
    }
}
