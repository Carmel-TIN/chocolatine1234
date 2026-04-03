##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC	=	clang

CFLAGS	=	-Wall -Wextra -I./include

SRC	=	pong.c

OBJ	=	$(SRC:.c=.o)

NAME	=	101pong

all:		
	$(CC) $(SRC) -o $(NAME) -lm

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	find . -name "*~" -delete
	find . -name "#*#" -delete

re:	fclean all

.PHONY:	all clean fclean re
