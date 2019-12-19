/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2019
** File description:
** my_memset
*/

#include "my.h"

void my_memset(void *mem, int val, size_t i)
{
    char *tmp = (char *)mem;

    for (size_t x = 0; x < i; x++)
        tmp[x] = val;
}
