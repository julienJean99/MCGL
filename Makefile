# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 18 Feb 22:11:38 CET 2019
# // Makefile
# //

SRC = src/modular/new.c

OBJ = $(SRC:.c=.o)

CC = gcc

NAME = libMcgl.so

LDFLAGS = -shared

CFLAGS = -fPIC -W -Wall -Wextra -Iinclude/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	make -C tests/

.PHONY: clean fclean re $(NAME) test
