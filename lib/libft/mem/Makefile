NAME			:= libftmem.a

SRC				:= \
				./ft_bzero.c \
				./ft_calloc.c \
				./ft_dirtyswap.c \
				./ft_memchr.c \
				./ft_memcmp.c \
				./ft_memcpy.c \
				./ft_memmove.c \
				./ft_memset.c


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
