CC = gcc
CFLAGS = -Wall -fPIC -O0 -g3
LDFLAGS = -shared -ldl

NAME = fault_injector.so
SRC = fault_injector.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

