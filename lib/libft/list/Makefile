NAME			:= libftlist.a

SRC				:= \
				./ft_lstadd_back_bonus.c \
				./ft_lstadd_front_bonus.c \
				./ft_lstarr.c \
				./ft_lstclear_bonus.c \
				./ft_lstdelone_bonus.c \
				./ft_lstget_bonus.c \
				./ft_lstiter_bonus.c \
				./ft_lstiter_param_bonus.c \
				./ft_lstlast_bonus.c \
				./ft_lstmap_bonus.c \
				./ft_lstnew_bonus.c \
				./ft_lstpop.c \
				./ft_lstsize_bonus.c


OBJDIR			:= obj
OBJ				:= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# module dependencies
DEPS			:= mem

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
