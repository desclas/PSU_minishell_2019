/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** my_calloc
*/

#include "my.h"

void *my_calloc(size_t size)
{
    void *ptr = malloc(size);

    for (size_t i = 0; i < size; i++)
        ((char *)ptr)[i] = 0;
    return (ptr);
}
