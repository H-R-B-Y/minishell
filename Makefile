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

# $(SRC_DIR)/lexar/cleanse_validate_tokens.c \
# $(SRC_DIR)/lexar/token_binning.c \
# $(SRC_DIR)/lexar/token_init.c \
# $(SRC_DIR)/lexar/token_operators.c \
# $(SRC_DIR)/lexar/token_skipping.c \
# $(SRC_DIR)/lexar/token_util.c \
# $(SRC_DIR)/lexar/token_util2.c \
# $(SRC_DIR)/lexar/tokeniser.c \
#

# $(SRC_DIR)/new_lexar/check_errors.c \
# $(SRC_DIR)/new_lexar/quote_isnt_escaped.c \
# $(SRC_DIR)/new_lexar/set_error.c \
# $(SRC_DIR)/new_lexar/token_binning.c \
# $(SRC_DIR)/new_lexar/token_continuation.c \
# $(SRC_DIR)/new_lexar/token_init.c \
# $(SRC_DIR)/new_lexar/token_operators.c \
# $(SRC_DIR)/new_lexar/token_skip.c \
# $(SRC_DIR)/new_lexar/token_skipping.c \
# $(SRC_DIR)/new_lexar/token_util.c \
# $(SRC_DIR)/new_lexar/token_util2.c \
# $(SRC_DIR)/new_lexar/tokenise_begin.c \
# $(SRC_DIR)/new_lexar/tokenise.c \

# $(SRC_DIR)/readline_loop/readline_cleanup.c \
# $(SRC_DIR)/readline_loop/readline_loop_execution.c \
# $(SRC_DIR)/readline_loop/readline_loop.c \


SRCS			:= \
				$(SRC_DIR)/fsm_tokeniser/fsm_tokeniser.c \
				src/fsm_tokeniser/fsm_utils.c \
				src/fsm_tokeniser/token_operators.c \
				$(SRC_DIR)/fsm_tokeniser/token_skipping.c \
				$(SRC_DIR)/fsm_tokeniser/tokeniser.c \
				\
				$(SRC_DIR)/syntax_tree/ast_node_init.c \
				$(SRC_DIR)/syntax_tree/print_ast.c \
				$(SRC_DIR)/syntax_tree/produce_syntax_tree.c \
				$(SRC_DIR)/syntax_tree/syntax_consume.c \
				$(SRC_DIR)/syntax_tree/syntax_heirarchy.c \
				$(SRC_DIR)/syntax_tree/syntax_util.c \
				\
				$(SRC_DIR)/utility/pop_line.c \
				$(SRC_DIR)/utility/str_join_with_sep.c \
				$(SRC_DIR)/utility/str_vec_join.c \
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
		@$(MAKE) --directory $(LIBFT_DIR) fclean 
		@rm -rf $(OBJS)
		@find . -name '*.gcda' -delete
		@find . -name '*.gcno' -delete

rm:
		@$(MAKE) --directory $(LIBFT_DIR) fclean
		@rm -rf $(NAME)
		@rm -rf checker

fclean: clean rm pre post

re: fclean all

norm:
		@python3 tools/norm_toline/norm_to_line.py ./include ./src

pre:
		@echo
		@echo "   /)  /)",
		@echo " ପ(˶•-•˶)ଓ ♡",
		@echo -n "  /づ  づ ˚₊‧꒰$(NAME) :: $(MAKECMDGOALS) :: Wait  ꒱ ‧₊˚⭒"

post:
		@echo "\b\b\b\b\b\b\b\b\b\b\b\b\bDone  ꒱ ‧₊˚⭒"
		@echo 

.PHONY: all clean fclean re test pre post rm coverage norm

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
