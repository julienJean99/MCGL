# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Mon 20 May 20:25:35 CEST 2019
# // source
# //

DRAWABLE = drawable.c	\
		point.c		\
		line.c			\
		cercle.c		\
		text.c			\
		image.c

CLASS = window.c	\
	$(addprefix drawable/, $(DRAWABLE))

INTERNAL = connect_to_server.c

MODULAR = new.c	\
		list.c

PNG = openPng.c

IMAGE = $(addprefix png/, $(PNG))

SRC := $(addprefix src/modular/, $(MODULAR))	\
	$(addprefix src/class/, $(CLASS))			\
	$(addprefix src/internal/, $(INTERNAL))	\
	$(addprefix src/image/, $(IMAGE))
