##
## EPITECH PROJECT, 2019
## 	MCGL
## File description:
## tests make files
##

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	mv $@ $(ROOT)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(ROOT)$(NAME)

re: fclean all
