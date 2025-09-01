NAME			:= libftarray.a

SRC				:= \
				./ft_arradd_atindex.c \
				./ft_arradd_back.c \
				./ft_arradd_front.c \
				./ft_arrclear.c \
				./ft_arrdel_atindex.c \
				./ft_arrfree.c \
				./ft_arriter.c \
				./ft_arrjoin.c \
				./ft_arrlcat.c \
				./ft_arrlen.c \
				./ft_arrlist.c \
				./ft_arrmap.c



# Use a single object directory for all objects
OBJDIR			:= obj
OBJ			:= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# module dependencies
DEPS			:= mem string

CC				:= gcc
AR				:= ar rcs
CFLAGS			:= -Wall -Wextra -Werror
INCLUDE			:= -I$(INCDIR)

INCDIR			?= ../include

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
