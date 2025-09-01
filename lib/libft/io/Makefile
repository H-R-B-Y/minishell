NAME			:= libftio.a

SRC			:= \
				./ft_putchar_fd.c \
				./ft_putendl_fd.c \
				./ft_putnbr_fd.c \
				./ft_putstr_fd.c \
				./printf/prefix_padding.c \
				./printf/precision.c \
				./printf/general_functions.c \
				./printf/generators.c \
				./printf/ft_printf.c \
				./printf/escape_parsing.c \
				./printf/conversion_functions.c \
				./printf/conv_factory.c \
				./printf/bitflags.c \
				./gnl/get_next_line.c \
				./gnl/get_next_line_utils.c


OBJDIR			:= obj
OBJ				:= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
vpath %.c . ./printf ./gnl

# module dependencies
DEPS			:= mem conv ctype string

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
