/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** my_puterr
*/

#include "my.h"

void my_puterr(char *str)
{
    write(2, str, my_strlen(str));
}
