# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 18 Feb 22:11:38 CET 2019
# // Makefile Unit test
# //

ROOT = ../

CC = clang

LD = clang

CPPFLAGS = -I$(ROOT)include/

CFLAGS = -W -Wall -Wextra -g

LDLIBS = -lMcgl

LDFLAGS = -L..

SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = test

include rules.mk

.PHONY: clean fclean re $(NAME) test
