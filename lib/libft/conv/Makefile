NAME			:= libftconv.a

SRC				:= \
				./ft_atof.c \
				./ft_atoi.c \
				./ft_itoa.c


OBJDIR			:= obj
OBJ				:= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# module dependencies
DEPS			:= ctype

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
