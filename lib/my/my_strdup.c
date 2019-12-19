/*
** EPITECH PROJECT, 2019
** CPool_infinadd_2019
** File description:
** my_strdup
*/

#include "my.h"

char *my_strdup(char *str)
{
    char *res = my_calloc(sizeof(char) * (my_strlen(str) + 1));

    my_strcpy(res, str);
    return (res);
}
