NAME			:= libftbitflags.a

SRC				:= \
				./bit_has_all_flags.c \
				./bit_has_flag.c \
				./bit_has_some_flags.c \
				./bit_set_flags.c \
				./bit_toggle_flags.c \
				./bit_unset_flags.c \
				\



OBJDIR			:= obj
OBJ				:= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# module dependencies
DEPS			:= 

CC				:= gcc
AR				:= ar rcs
CFLAGS			:= -Wall -Wextra -Werror
INCLUDE			:= -I$(INCDIR)

all: $(LIBDIR)/$(NAME)

$(LIBDIR)/$(NAME): $(OBJ) | $(LIBDIR)
	for dep in $(DEPS); do \
		 $(MAKE) -C ../$$dep LIBDIR=$(LIBDIR) INCDIR=$(INCDIR); \
	done
	$(AR) $@ $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBDIR):
	mkdir -p $(LIBDIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIBDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
