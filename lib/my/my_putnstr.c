/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** my_putnstr
*/

#include "my.h"

void my_putnstr(char *str, size_t n)
{
    write(1, str, n);
}
