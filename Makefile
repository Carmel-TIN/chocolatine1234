##
## EPITECH PROJECT, 2025
## projet
## File description:
## description
##

CC	=	clang

NAME 	=	mysh

CFLAGS	=	-Wall -Wextra

SRCS	=	utils/my_putnbr_fd.c	\
			utils/my_putnbr_recursive.c	\
			utils/my_putstr_fd.c	\
			utils/my_str_to_word_array.c	\
			utils/my_strcat.c	\
			utils/my_strcmp.c	\
			utils/my_strcpy.c	\
			utils/my_strdup.c	\
			utils/my_strlen.c	\
			utils/my_strncmp.c	\
			utils/my_getnbr.c	\
			src/main_loop.c	\
			src/find_absolute_path.c	\
			src/exec_cmd.c	\
			src/handle_env.c	\
			src/handle_sig.c	\
			src/built_in_cd.c	\
			src/built_in_env.c	\
			src/built_in_exit.c	\
			src/built_in_setenv.c	\
			src/built_in_unsetenv.c	\
			src/my_prompt.c	\
			src/main.c	\
			src/rm_spaces.c	\
			src/parse_pipe.c	\
			src/exec_pipeline.c	\
			src/parse_redir.c	\
			src/free_list.c

SRC_WITHOUT_MAIN	=	utils/my_getnbr.c	\
						utils/my_strdup.c	\
						utils/my_strlen.c	\
						utils/my_strcpy.c

OBJS	=	$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(SRCS) -o $(NAME) -I./include/ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests

unit_tests: fclean
	${CC} -o unit_tests $(SRC_WITHOUT_MAIN) tests/test_minishell.c --coverage -lcriterion
	
tests_run: unit_tests
	./unit_tests

re: fclean all

.PHONY: all clean fclean re
