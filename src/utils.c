/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** utils
*/

#include "minishell.h"

char **my_append_char_tab(char **tab, char *str)
{
    char **res = NULL;
    size_t i;

    for (i = 0; tab[i] != NULL; i++);
    res = my_calloc(sizeof(*res) * (i + 2));
    for (i = 0; tab[i] != NULL; i++)
        res[i] = tab[i];
    res[i] = str;
    res[i + 1] = NULL;
    free(tab);
    return (res);
}

int pass_quote(char *str)
{
    int i = 0;

    for (int z = i; (IS_QUOTE(str[z])) && (z == i || str[z] != str[i]); i++);
    return (i);
}

char **my_nstr_to_wordtab(char *str, int nb)
{
    char **res;

    if (str[0] == '\0')
        return (NULL);
    res = my_calloc(sizeof(*res));
    for (int i = 0, x = 0; i < nb; i++) {
        for (x = i; str[i] != ' ' && str[i] != '\0'; i++)
            i += pass_quote(&str[i]);
        res = my_append_char_tab(res, my_strndup(&str[x], i - x));
    }
    return (res);
}

cmds_t *add_dlist(cmds_t *l1, cmds_t *l2)
{
    cmds_t *tmp = l1;

    if (l1 == NULL)
        return (l2);
    for (; tmp->next != NULL; tmp = tmp->next);
    l2->prev = tmp;
    tmp->next = l2;
    return (l1);
}
