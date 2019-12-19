/*
** EPITECH PROJECT, 2019
** CPool_bistro-matic_2019
** File description:
** my_append_str
*/

#include "my.h"

char *my_append_str(char *str, char *c)
{
    size_t len = my_strlen(str) + my_strlen(c);
    char *res = my_calloc(sizeof(char) * (len + 1));

    for (size_t i = 0, x = 0; str[i] != '\0' || c[x] != '\0';) {
        if (str[i] != 0) {
            res[i + x] = str[i];
            i++;
        } else {
            res[i + x] = c[x];
            x++;
        }
    }
    res[len] = '\0';
    free(str);
    free(c);
    return (res);
}
