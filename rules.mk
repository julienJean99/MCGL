# //
# // This document created by Julien JEAN
# // For project : MCGL
# //
# // Fri  8 Mar 15:07:53 CET 2019
# // makefile rules
# //

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/.:
	mkdir -p $@

$(OBJ_DIR)%/.:
	mkdir -p $@

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: override CPPFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
$(OBJ_DIR)/%.o: %.c | $$(@D)/.
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C tests/ clean

fclean: clean
	$(RM) $(NAME)
	make -C tests/ fclean

re: fclean all

doc:
	doxygen MCGL

test: CFLAGS += -g3
test: $(NAME)
	make -C tests/

.PRECIOUS: $(OBJ_DIR)/. $(OBJ_DIR)%/.

-include $(OBJ:.o=.d)
