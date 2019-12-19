/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** my_epurstr
*/

#include "my.h"

void my_epurstr(char *str)
{
    for (; str[0] == ' ' || str[0] == '\t';)
        for (size_t i = 0; str[i] != '\0'; i++)
            str[i] = str[i + 1];
    for (size_t i = 0; str[i] != '\0'; i++) {
        for (size_t x = i + 1; (str[i] == ' ' || str[i] == '\t') &&
            str[x] != '\0' && (str[x] == ' ' || str[x] == '\t'); x++)
            str[x] = str[x + 1];
        if (str[i] == ' ' || str[i] == '\t')
            str[i] = (str[i] == '\t') ? ' ' : str[i];
    }
}
