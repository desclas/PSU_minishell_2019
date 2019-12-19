/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** my_strndup
*/

#include "my.h"

char *my_strndup(char *str, int nb)
{
    char *res = my_calloc(sizeof(char) * (nb + 1));

    for (int i = 0; i < nb; i++)
        res[i] = str[i];
    return (res);
}
