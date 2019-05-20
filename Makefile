# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 18 Feb 22:11:38 CET 2019
# // Makefile
# //

CC = gcc

CFLAGS = -fPIC -W -Wall -Wextra

CPP = $(CC)

CPPFLAGS = -Iinclude/

LD = $(CC)

LDLIBS = -lX11 -lpng

LDFLAGS = -shared

NAME = libMcgl.so

OBJ_DIR = obj

include source.mk

override OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

include rules.mk

.PHONY: all clean fclean re test
