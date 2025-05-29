NAME			:= minishell
CC 				:= gcc
CFLAGS			:= -Wextra -Wall -Werror -g3
#CFLAGS			:= 

ifdef debug
endif
CFLAGS += -DFD_DBG=3

MAKEFLAGS		+= --no-print-directory

LIBFLAGS		:= -lreadline -lhistory

HEADERS			:= -Iinclude

LIB_DIR			:= ./lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src

SRCS			:= \
				$(SRC_DIR)/builtins/builtin_cd.c \
				$(SRC_DIR)/builtins/builtin_echo.c \
				$(SRC_DIR)/builtins/builtin_env.c \
				$(SRC_DIR)/builtins/builtin_exit.c \
				$(SRC_DIR)/builtins/builtin_export.c \
				$(SRC_DIR)/builtins/builtin_pwd.c \
				$(SRC_DIR)/builtins/builtin_unset.c \
				$(SRC_DIR)/builtins/utility_funcs.c \
				\
				$(SRC_DIR)/debugger/adding_items.c \
				$(SRC_DIR)/debugger/init_debugger.c \
				$(SRC_DIR)/debugger/write_ast.c \
				$(SRC_DIR)/debugger/write_states.c \
				$(SRC_DIR)/debugger/write_tokens.c \
				\
				$(SRC_DIR)/fsm_tokeniser/fsm_tokeniser.c \
				$(SRC_DIR)/fsm_tokeniser/fsm_utils.c \
				$(SRC_DIR)/fsm_tokeniser/token_binning.c \
				$(SRC_DIR)/fsm_tokeniser/token_handlers.c \
				$(SRC_DIR)/fsm_tokeniser/token_printing.c \
				$(SRC_DIR)/fsm_tokeniser/token_skipping.c \
				$(SRC_DIR)/fsm_tokeniser/token_utils.c \
				$(SRC_DIR)/fsm_tokeniser/tokeniser.c \
				\
				$(SRC_DIR)/heredoc_handler.c/handle_heredoc.c \
				\
				$(SRC_DIR)/new_readline_loop/read_command_loop.c \
				$(SRC_DIR)/new_readline_loop/splitting_next_lines.c \
				\
				$(SRC_DIR)/syntax_tree/ast_node_init.c \
				$(SRC_DIR)/syntax_tree/print_ast.c \
				$(SRC_DIR)/syntax_tree/produce_syntax_tree.c \
				$(SRC_DIR)/syntax_tree/syntax_consume.c \
				$(SRC_DIR)/syntax_tree/syntax_heirarchy.c \
				$(SRC_DIR)/syntax_tree/syntax_util.c \
				\
				$(SRC_DIR)/utility/operators.c \
				$(SRC_DIR)/utility/pop_line.c \
				$(SRC_DIR)/utility/remove_quotes.c \
				$(SRC_DIR)/utility/sgetenv.c \
				$(SRC_DIR)/utility/sgetenvany.c \
				$(SRC_DIR)/utility/ssetenv.c \
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
		$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) $(LIBFLAGS) -o $(NAME)
		@echo "\b\b\b\b\b\b\b\b\b\b\b\b\bDone  ꒱ ‧₊˚⭒"
		@echo 

# testing: $(OBJS) $(LIBFT) ./include/minishell.h
# 	@$(CC) $(CFLAGS) src/testing.c $(OBJS) $(LIBFT) $(LIBFLAGS) -o $(NAME)

$(LIBFT):
		@$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)" CC=$(CC)

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
