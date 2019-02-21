# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 18 Feb 22:11:38 CET 2019
# // Makefile
# //

OBJ = $(SRC:.c=.o)

CC = gcc

NAME = libMcgl.so

LDFLAGS = -shared

CFLAGS = -fPIC -W -Wall -Wextra -Iinclude/ -g3

CLASS = window.c

MODULAR = new.c

INTERNAL = connect_to_server.c

SRC = $(addprefix src/modular/, $(MODULAR))	\
	$(addprefix src/class/, $(CLASS))			\
	$(addprefix src/internal/, $(INTERNAL))

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
