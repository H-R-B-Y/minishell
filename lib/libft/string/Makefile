NAME			:= libftstring.a

SRC				:= \
				./ft_split.c \
				./ft_splitfn.c \
				./ft_splitquoted.c \
				./ft_strchr_i.c \
				./ft_strchr.c \
				./ft_strcmp.c \
				./ft_strcountchar.c \
				./ft_strdup.c \
				./ft_striteri.c \
				./ft_strjoin.c \
				./ft_strlcat.c \
				./ft_strlcpy.c \
				./ft_strlen.c \
				./ft_strltrim.c \
				./ft_strmapi.c \
				./ft_strncmp.c \
				./ft_strndup.c \
				./ft_strnstr.c \
				./ft_strrchr.c \
				./ft_strrtrim.c \
				./ft_strtrim.c \
				./ft_substr.c


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
