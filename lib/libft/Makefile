# Where built archives should end up
LIBDIR			:= lib
INCDIR			:= ./include

CFLAGS			:= -Wall -Wextra -Werror -std=c99


SUBMODULES		:= mem conv ctype list array io rand string cdll math hashmap mpmc_ringbuff

# Work out how to conditionally add modules that are not in the list of submodles
# for things like gnu source threading with atomics 

# Final merged library
NAME			:= libft.a

.PHONY: all $(SUBMODULES) clean fclean re

# Build all submodules and merge into final library
all: $(NAME)

lib: $(NAME)

# Build each submodule (ensures dependencies are built first)
$(SUBMODULES):
	+$(MAKE) -C $@ LIBDIR=$(abspath $(LIBDIR)) INCDIR=$(abspath $(INCDIR)) CFLAGS="$(CFLAGS)"


# Merge all submodule archives into one
$(NAME): $(SUBMODULES)
	@mkdir -p $(LIBDIR)
	@rm -f $@
	@for mod in $(SUBMODULES); do \
		ar x $(LIBDIR)/libft$${mod#mem}.a 2>/dev/null || ar x $(LIBDIR)/libft$${mod}.a; \
	 done
	$(AR) rcs $@ *.o
	@rm -f *.o

clean:
	for mod in $(SUBMODULES); do \
		$(MAKE) -C $$mod clean; \
	done


fclean: clean
	for mod in $(SUBMODULES); do \
		$(MAKE) -C $$mod fclean LIBDIR=$(abspath $(LIBDIR)); \
	done
	rm -f $(NAME)
	rm -rf $(LIBDIR)

re: fclean all
