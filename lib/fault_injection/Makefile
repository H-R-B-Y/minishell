CC = gcc
CFLAGS = -Wall -fPIC -O0 -g3
LDFLAGS = -shared -ldl

NAME = faultinject.so
SRC = src.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

