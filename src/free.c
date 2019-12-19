/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** free
*/

#include "minishell.h"

void free_char_tab(char **tab)
{
    if (tab != NULL) {
        for (size_t i = 0; tab[i] != NULL; i++)
            free(tab[i]);
        free(tab);
    }
}

long free_fcmds(cmds_t *list, cmds_t *solo)
{
    if (solo != NULL) {
        (solo->cmd != NULL) ? free(solo->cmd) : 0;
        (solo->rred != NULL) ? free(solo->rred) : 0;
        (solo->wred != NULL) ? free(solo->wred) : 0;
        (solo->args != NULL) ? free_char_tab(solo->args) : 0;
        free(solo);
    }
    if (list != NULL)
        for (cmds_t *tmp = list->next; list != NULL; list = tmp) {
            tmp = (tmp != NULL) ? list->next : tmp;
            (list->cmd != NULL) ? free(list->cmd) : 0;
            (list->rred != NULL) ? free(list->rred) : 0;
            (list->wred != NULL) ? free(list->wred) : 0;
            (list->args != NULL) ? free_char_tab(list->args) : 0;
            free(list);
        }
    return (0);
}

void free_ucmd(cmds_t **start, cmds_t *end)
{
    cmds_t *tmp = NULL;

    if (*start != NULL && end != NULL) {
        for (tmp = (*start)->next; *start != end; *start = tmp) {
            tmp = (tmp != NULL) ? (*start)->next : tmp;
            ((*start)->cmd != NULL) ? free((*start)->cmd) : 0;
            ((*start)->rred != NULL) ? free((*start)->rred) : 0;
            ((*start)->wred != NULL) ? free((*start)->wred) : 0;
            ((*start)->args != NULL) ? free_char_tab((*start)->args) : 0;
            free(*start);
        }
        tmp = (*start)->next;
        ((*start)->cmd != NULL) ? free((*start)->cmd) : 0;
        ((*start)->rred != NULL) ? free((*start)->rred) : 0;
        ((*start)->wred != NULL) ? free((*start)->wred) : 0;
        ((*start)->args != NULL) ? free_char_tab((*start)->args) : 0;
        free(*start);
        *start = tmp;
    }
}
