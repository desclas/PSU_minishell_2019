/*
** EPITECH PROJECT, 2019
** CPool_Day04_2019
** File description:
** my_putstr
*/

#include "my.h"

int my_putstr(const char *str)
{
    return (write(1, str, my_strlen(str)));
}
