# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 18 Feb 22:11:38 CET 2019
# // Makefile Unit test
# //

ROOT = ../

INCLUDE = -I$(ROOT)include/

SRC_BASE = $(ROOT)src

SRC =

OBJ = $(SRC:.c=.o)

CC = clang

NAME = Unit_test

LDFLAGS = -lcriterion --coverage

CFLAGS = -W -all -Wextra --coverage $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	./$(NAME)
clean:
	find $(ROOT) -name "*.gcda" -delete
	find $(ROOT) -name "*.gcno" -delete
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	make -C tests/

.PHONY: clean fclean re $(NAME) test
