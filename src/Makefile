##
## EPITECH PROJECT, 2019
## CPool_finalstumper_2019
## File description:
## Makefile
##

DEBUG =
ifeq ($(DEBUG),yes)
CFLAGS	=	-Iinclude -W -Wall -Wextra -Werror -g3
else
CFLAGS	=	-Iinclude -W -Wall -Wextra -Werror
endif

NAME	=	mysh

SRC	=	main.c					\
		execute.c				\
		utils.c					\
		access.c				\
		builtin.c				\
		free.c					\
		prompt.c				\
		make_cd.c				\
		builtin_env.c			\
		utils_red.c				\
		check_quote.c

OBJ	=	$(SRC:.c=.o)

LDFLAGS	=	-L../lib/my -lmy

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)
	cp $@ ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re rush3
