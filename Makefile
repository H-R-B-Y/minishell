NAME			:= minishell
CC 				:= gcc
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 #-fsanitize=address
#CFLAGS			:= 

ifdef debug
CFLAGS += -DFD_DBG=3
endif

MAKEFLAGS		+= --no-print-directory

LIBFLAGS		:= -lreadline -lhistory

HEADERS			:= -Iinclude

LIB_DIR			:= ./lib

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src

SRCS			:= \
				$(SRC_DIR)/better_prompt/git_stuff.c \
				$(SRC_DIR)/better_prompt/prompt_setup.c \
				\
				$(SRC_DIR)/builtins/builtin_cd.c \
				$(SRC_DIR)/builtins/builtin_.c \
				$(SRC_DIR)/builtins/builtin_echo.c \
				$(SRC_DIR)/builtins/builtin_env.c \
				$(SRC_DIR)/builtins/builtin_exit.c \
				$(SRC_DIR)/builtins/builtin_export.c \
				$(SRC_DIR)/builtins/builtin_pwd.c \
				$(SRC_DIR)/builtins/builtin_unset.c \
				$(SRC_DIR)/builtins/utility_funcs.c \
				\
				$(SRC_DIR)/execution/execution.c \
				$(SRC_DIR)/execution/execute_command.c \
				$(SRC_DIR)/execution/execute_pipe.c \
				$(SRC_DIR)/execution/execute_subshell.c \
				$(SRC_DIR)/execution/execute_seq.c \
				$(SRC_DIR)/execution/execute_logical.c \
				$(SRC_DIR)/execution/cmd_prep_utils.c \
				$(SRC_DIR)/execution/glob_local_dir.c \
				$(SRC_DIR)/execution/rd_map_fds.c \
				$(SRC_DIR)/execution/rd_prep_fds.c \
				$(SRC_DIR)/execution/rd_list_restore.c \
				$(SRC_DIR)/execution/rd_utils.c \
				$(SRC_DIR)/execution/path_prep_utils.c \
				$(SRC_DIR)/execution/get_exec_cmd.c \
				\
				$(SRC_DIR)/debugger/adding_items.c \
				$(SRC_DIR)/debugger/debugger_util.c \
				$(SRC_DIR)/debugger/init_debugger.c \
				$(SRC_DIR)/debugger/write_ast.c \
				$(SRC_DIR)/debugger/write_end.c \
				$(SRC_DIR)/debugger/write_states.c \
				$(SRC_DIR)/debugger/write_tokens.c \
				\
				$(SRC_DIR)/fsm_tokeniser/realize_token.c \
				$(SRC_DIR)/fsm_tokeniser/tokeniser_return.c \
				$(SRC_DIR)/fsm_tokeniser/string_condition.c \
				$(SRC_DIR)/fsm_tokeniser/fsm_tokeniser.c \
				$(SRC_DIR)/fsm_tokeniser/fsm_utils.c \
				$(SRC_DIR)/fsm_tokeniser/token_binning.c \
				$(SRC_DIR)/fsm_tokeniser/token_handlers.c \
				$(SRC_DIR)/fsm_tokeniser/token_printing.c \
				$(SRC_DIR)/fsm_tokeniser/token_skipping.c \
				$(SRC_DIR)/fsm_tokeniser/token_utils.c \
				$(SRC_DIR)/fsm_tokeniser/tokeniser.c \
				\
				$(SRC_DIR)/heredoc_handler/handle_heredoc.c \
				$(SRC_DIR)/heredoc_handler/handle_redirects.c \
				$(SRC_DIR)/heredoc_handler/heredoc_reader.c \
				\
				$(SRC_DIR)/init_process/check_openfds.c \
				$(SRC_DIR)/init_process/init_process.c \
				$(SRC_DIR)/init_process/parse_limits.c \
				$(SRC_DIR)/init_process/restore_signals.c \
				$(SRC_DIR)/init_process/shell_utils.c \
				$(SRC_DIR)/init_process/signal_handlers.c \
				\
				$(SRC_DIR)/new_readline_loop/read_command_loop.c \
				$(SRC_DIR)/new_readline_loop/readline_wrapper.c \
				$(SRC_DIR)/new_readline_loop/splitting_next_lines.c \
				\
				$(SRC_DIR)/syntax_tree/add_redirect_types.c \
				$(SRC_DIR)/syntax_tree/ast_node_init.c \
				$(SRC_DIR)/syntax_tree/consume_command.c \
				$(SRC_DIR)/syntax_tree/consume_subshell.c \
				$(SRC_DIR)/syntax_tree/print_ast.c \
				$(SRC_DIR)/syntax_tree/produce_syntax_tree.c \
				$(SRC_DIR)/syntax_tree/syntax_heirarchy.c \
				$(SRC_DIR)/syntax_tree/syntax_util.c \
				\
				$(SRC_DIR)/utility/var_expansion/special_expansion.c \
				$(SRC_DIR)/utility/var_expansion/var_checks.c \
				$(SRC_DIR)/utility/var_expansion/expand_and_split.c \
				$(SRC_DIR)/utility/var_expansion/handle_word_split.c \
				$(SRC_DIR)/utility/var_expansion/special_expansion_utils.c \
				$(SRC_DIR)/utility/var_expansion/special_expansion_utils2.c \
				$(SRC_DIR)/utility/arrjoin.c \
				$(SRC_DIR)/utility/get_my_pid.c \
				$(SRC_DIR)/utility/last_newline_not_end.c \
				$(SRC_DIR)/utility/operators.c \
				$(SRC_DIR)/utility/pop_line.c \
				$(SRC_DIR)/utility/rem_quotes.c \
				$(SRC_DIR)/utility/sgetenv.c \
				$(SRC_DIR)/utility/sgetenvany.c \
				$(SRC_DIR)/utility/set_cmd_envp.c \
				$(SRC_DIR)/utility/set_var_value.c \
				$(SRC_DIR)/utility/simple_split.c \
				$(SRC_DIR)/utility/ssetenv.c \
				$(SRC_DIR)/utility/str_join_with_sep.c \
				$(SRC_DIR)/utility/str_vec_join.c \
				$(SRC_DIR)/utility/update_env.c \
				$(SRC_DIR)/utility/set_n_envp.c \
				$(SRC_DIR)/utility/set_any_env.c \
				$(SRC_DIR)/utility/init_pwd.c \
				$(SRC_DIR)/utility/exit_handling_utils.c \
				\


BIN				:= \
				$(SRC_DIR)/builtins/raw_dump.bin\
				\

TEST_SCRIPT		:=

OBJS			:= $(BIN:.bin=.o) ${SRCS:.c=.o}

MAIN			:= $(SRC_DIR)/main.c

all: $(NAME)

$(NAME): $(MAIN) $(OBJS) $(LIBFT) ./include/minishell.h
		@printf "\n"
		@printf "   /)  /)\n"
		@printf " ପ(˶•-•˶)ଓ \033[38;2;250;0;150m♡\033[0m\n"
		@echo -n "  /づ  づ ˚₊‧꒰$(NAME) ::\033[38;2;150;0;150m Wait\033[0m  ꒱ ‧₊˚⭒"
		@$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) $(LIBFLAGS) -o $(NAME)
		@printf "\b\b\b\b\b\b\b\b\b\b\b\b\b\033[38;2;50;200;0mDone\033[0m  ꒱ ‧₊˚⭒"
		@printf "\n"

# testing: $(OBJS) $(LIBFT) ./include/minishell.h
# 	@$(CC) $(CFLAGS) src/testing.c $(OBJS) $(LIBFT) $(LIBFLAGS) -o $(NAME)

$(LIBFT):
		@$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)" CC=$(CC)

%.o: %.c
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

%.o: %.bin
	@ld -r -b binary -o $@ $<

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
		@printf "\n"
		@printf "   /)  /)\n"
		@printf " ପ(˶•-•˶)ଓ \033[38;2;250;0;150m♡\033[0m\n"
		@printf "  /づ  づ ˚₊‧꒰$(NAME) :: $(MAKECMDGOALS) ::\033[38;2;150;0;150m Wait\033[0m  ꒱ ‧₊˚⭒"

post:
		@printf "\b\b\b\b\b\b\b\b\b\b\b\b\b\033[38;2;0;200;0mDone\033[0m  ꒱ ‧₊˚⭒\n"
		@printf "\n"

.PHONY: all clean fclean re test pre post rm coverage norm

valgrind:
	@printf "valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all -s --suppressions=supp.supp ./minishell"

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
