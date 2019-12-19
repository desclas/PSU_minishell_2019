/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** my_ultoa
*/

#include "my.h"

char *my_ultoa(unsigned long nb)
{
    char *res = my_calloc(sizeof(char));

    if (nb == 0)
        res = my_append_char(res, '0');
    for (; nb != 0;) {
        res = my_append_char(res, (nb % 10) + '0');
        nb -= (nb % 10);
        nb /= 10;
    }
    return (my_revstr(res));
}
