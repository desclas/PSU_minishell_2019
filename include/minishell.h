/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2019
** File description:
** minishell
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "my.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define IS_ALPHANUM(x) (((x <= '9' && x >= '0') || (x <= 'z' && x >= 'a') ||\
    (x <= 'Z' && x >= 'A') || x == '_' || x == '-'))
#define IS_NUM(x) ((x <= '9' && x >= '0'))
#define IS_QUOTE(x) ((x == '"' || x == '\'' || x == '`'))
#define IS_REDIREC(x) ((x == '|' || x == '<' || x == '>'))
#define IS_SREDIREC(x) ((x == '|' || x == '<' || x == '>' || x == ';'))
#define IS_SEMI(x) ((x == ';'))

typedef struct cmds {
    char *cmd;
    char **args;
    char *rred;
    char *wred;
    int pfd[2];
    pid_t pid;
    struct cmds *next;
    struct cmds *prev;
} cmds_t;

// execute.c
cmds_t *exec_cmds(cmds_t *list, char ***env);

// utilis.c
int pass_quote(char *str);
char **my_nstr_to_wordtab(char *str, int nb);
cmds_t *add_dlist(cmds_t *l1, cmds_t *l2);
char **my_append_char_tab(char **, char *);

// free.c
void free_char_tab(char **tab);
long free_fcmds(cmds_t *list, cmds_t *solo);
void free_ucmd(cmds_t **start, cmds_t *end);

// access.c
int access_it(cmds_t *cmd, char **env);

// check_quote.c
int check_quote(char *line);

// utils_red.c
void exit_error(cmds_t *list, char **env, char *msg);
void read_red(cmds_t *list, char **env);
void write_red(cmds_t *list, char **env);

// prompt.c
cmds_t *get_prompt(char **env);

// builtin.c
int is_builtin(cmds_t *list, char ***env);
void print_env(cmds_t *list, char ***env);

// make_cd.c
void make_cd(cmds_t *list, char ***env);

// builtin_env.c
void set_env(char ***env, char *name, char *value);
void preset_env(cmds_t *list, char ***env);
void unset_env(cmds_t *list, char ***env);

#endif /* !MINISHELL_H_ */
