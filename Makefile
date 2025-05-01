NAME			:= minishell
CFLAGS			:= -Wextra -Wall -Werror -O0 -g3
#CFLAGS			:= 

MAKEFLAGS		+= --no-print-directory

LIBFLAGS		:= -lreadline

HEADERS			:= -Iinclude

LIB_DIR			:= ./lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src
SRCS			:= \
				$(SRC_DIR)/lexar/token_binning.c \
				$(SRC_DIR)/lexar/token_init.c \
				$(SRC_DIR)/lexar/token_util.c \
				$(SRC_DIR)/lexar/tokeniser.c \
				\

TEST_SCRIPT		:=

OBJS			:= ${SRCS:.c=.o}

MAIN			:= $(SRC_DIR)/main.c

all: $(NAME)

$(NAME): $(MAIN) $(OBJS) $(LIBFT) ./include/minishell.h
		@echo
		@echo "   /)  /)",
		@echo " ପ(˶•-•˶)ଓ ♡",
		@echo -n "  /づ  づ ˚₊‧꒰$(NAME) :: Wait  ꒱ ‧₊˚⭒"
		@$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) $(LIBFLAGS) -o $(NAME)
		@echo "\b\b\b\b\b\b\b\b\b\b\b\b\bDone  ꒱ ‧₊˚⭒"
		@echo 

$(LIBFT):
		@$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

.c.o:
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
		@$(MAKE) --directory $(LIBFT_DIR) clean 
		@rm -rf $(OBJS)
		@find . -name '*.gcda' -delete
		@find . -name '*.gcno' -delete

rm:
		@$(MAKE) --directory $(LIBFT_DIR) fclean
		@rm -rf $(NAME)
		@rm -rf checker

fclean: clean rm pre post

re: fclean all

pre:
		@echo
		@echo "   /)  /)",
		@echo " ପ(˶•-•˶)ଓ ♡",
		@echo -n "  /づ  づ ˚₊‧꒰$(NAME) :: $(MAKECMDGOALS) :: Wait  ꒱ ‧₊˚⭒"

post:
		@echo "\b\b\b\b\b\b\b\b\b\b\b\b\bDone  ꒱ ‧₊˚⭒"
		@echo 

.PHONY: all clean fclean re test pre post rm coverage

coverage:
ifeq ($(TEST_SCRIPT),)
	@printf "There has been an issue running coverage: no script to run program\n"
else
	@rm -rf coverage_reports
	@find . -name '*.gcda' -delete
	@make --directory . re CFLAGS="-fprofile-arcs -ftest-coverage" CC=gcc-10
	@bash -c $(TEST_SCRIPT)
	@sleep 2
	@mkdir -p coverage_reports
	@find . -name '*.gcda' -exec mv -n {} . \;
	@find . -name '*.gcno' -exec mv -n {} . \;
	@find . -name '*.c' -exec gcov-10 -o . {} \;  >> coverage_reports.txt
	@find . -name '*.gcov' -exec mv {} coverage_reports/ \;
	@find . -name '*.gcda' -delete
	@find . -name '*.gcno' -delete
endif

# reference for cleanup
# nm -C --defined-only *.o | grep ' T ' > defined.txt
# nm -C --undefined-only *.o > undefined.txt
