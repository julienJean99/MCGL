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

DRAWABLE = drawable.c	\
		point.c		\
		line.c			\
		cercle.c		\
		text.c			\
		image.c

CLASS = window.c	\
	$(addprefix drawable/, $(DRAWABLE))

INTERNAL = connect_to_server.c

MODULAR = new.c

PNG = openPng.c

IMAGE = $(addprefix png/, $(PNG))

SRC := $(addprefix src/modular/, $(MODULAR))	\
	$(addprefix src/class/, $(CLASS))			\
	$(addprefix src/internal/, $(INTERNAL))	\
	$(addprefix src/image/, $(IMAGE))

OBJ_DIR = obj

override OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

include rules.mk

.PHONY: all clean fclean re test
