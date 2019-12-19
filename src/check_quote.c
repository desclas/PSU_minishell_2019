/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** check_quote
*/

#include "minishell.h"

static int check_quote_loop(char *line, size_t *i, size_t *x)
{
    for (*x = *i, *i = *i + 1; IS_QUOTE(line[*x]); *i += 1) {
        if (line[*i] == line[*x])
            return (0);
        else if (line[*i] == '\0'){
            write(2, "Unmatch '", 10);
            write(2, &line[*x], 1);
            write(2, "'.\n", 3);
            return (1);
        }
        return (0);
    }
    return (0);
}

int check_quote(char *line)
{
    for (size_t i = 0, x = 0; line[i] != '\0'; i++)
        if (check_quote_loop(line, &i, &x) == 1)
            return (1);
    return (0);
}
