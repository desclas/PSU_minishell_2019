/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** my_ltoa
*/

#include "my.h"

char *my_ltoa(long nb)
{
    char *res = my_calloc(sizeof(char));
    char neg = 0;

    if (nb < 0) {
        neg = 0;
        nb *= -1;
    }
    if (nb == 0)
        res = my_append_char(res, '0');
    for (; nb != 0;) {
        res = my_append_char(res, (nb % 10) + '0');
        nb -= (nb % 10);
        nb /= 10;
    }
    if (neg)
        res = my_append_char(res, '-');
    return (my_revstr(res));
}
