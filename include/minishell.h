/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/08 17:03:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# ifndef __USE_POSIX
#  define __USE_POSIX
# endif
# ifndef __USE_POSIX199309
#  define __USE_POSIX199309
# endif
# ifndef SA_RESTART
#  include <asm-generic/signal-defs.h>
# endif
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <term.h>

# include "./libft.h"
# include "./ft_printf.h"
# include "./v_dbg.h"
# include "./readline_loop.h"
# include "./abstract_syntax_tree.h"
# include "./execution.h"
# include "./builtin.h"
# include "./ft_printf.h"

/**
 * @brief redo this comment
 * 
 */
typedef struct s_minishell	t_minishell;
struct s_minishell
{
	/// @brief Interactive mode flag (stdin is a terminal)
	short				interactive_mode;
	/// @brief signal handlers copied from the start of the process
	/// (so they can be restored)
	struct sigaction	old_handlers[32];
	/// @brief Environment array copied at the start of the process
	char				**environment;
	/// @brief Environment variables that have been created but unassigned
	char				**unassigned_env;
	/// @brief Shell local variables
	char				**local_env;
	/// @brief List of tokens relevant to the current job
	t_list				*tokens;
	/// @brief Tokens but as an array, for easier access
	t_token				**tokenv;
	/// @brief The execution tree relevant to the current job
	t_astnode			*current_tree;
	/// @brief PID of the shell
	pid_t				my_pid;
	/// @brief Return code of the previous command / job 
	int					return_code;
	/// @brief Internal information relevant to the finite state machine
	t_fsmdata			fsm_data;
	/// @brief Internal information relevant to the readline loop
	t_readline_data		rldata;
	///	@brief Last history item relevant to better_add_history
	char				*last_hist_item;
	/// @brief Current line (? do we still need this)
	char				*ecurrent_line;
	/// @brief Current pipeline (? do we still need this?)
	char				*current_pipeline;
	/// @brief Extra lines from input (? arent these in the rldata now?)
	char				**extra_lines;
	/// @brief Current prompt
	char				*prompt;
	/// @brief Data relevant for dumping binary data out to a fd
	struct s_dbg_info	info;
	/// @brief count of arguments passed to the program at execution
	int					argc;
	/// @brief arguments passed to program at execution
	char				**argv;
	char				*name;
	/// @brief limit for max file descriptors
	ssize_t				ulimit_n;
};

void			init_pwd(t_minishell *shell, char ***envp);
/**
 * @brief Initialise the shell
 * 
 * Checks for interactive mode,
 * Sets up signal handlers
 * Sets some config for libreadline
 * 
 * @param shell Reference to the shell
 * @param envp the environment passed in at start
 * @return int 0 is ok, < 0 is an error
 */
int				init_process(t_minishell *shell, char **envp);

/**
 * @brief Adds to readline history but does not duplicate
 * 
 * @param string The histeory item that we want to add
 * @return int status code
 */
int				better_add_history(t_minishell *shell, char *string);

/**
 * @brief Cleanup ready for the next command (or at ~ time)
 * 
 * This will free anything heap allocated so this doubles as
 * a safe way to cleanup.
 * 
 * @param shell Reference to the shell internals
 * @param rl_code readline code
 * (so we dont free anything that might be needed later)
 */
void			reset_for_command(t_minishell *shell,
					t_readline_retcode rl_code);

/**
 * @brief Creates the prompt with colours and git info
 * 
 * @param shell refernce to the shell object
 * @return char* the prompt! 
 */
char			*create_prompt(const t_minishell *shell);

/**
 * @brief print out a token list in columns
 * @param list the list of tokens to print
 * 
 * TODO: this should probably be moved to the input tokens header.
 */
void			print_token_list(const t_list *list);

// Utility functions:
// Some of these may be useful in libft?

/**
 * @brief join two string with a string in the middle
 * @param str1 the left half of the join
 * @param str2 the right half of the join
 * @param sep the seperator
 * 
 * for example "cat", "dog", " and " would produce:
 * cat and dog
 */
char			*str_join_with_sep(const char *str1,
					const char *str2, const char *sep);

/**
 * @brief join together a null terminated array of strings
 * 
 * @param arr a null terminated array of strings
 * @return char* joined string
 */
char			*str_vec_join(const char **arr);
/**
 * @brief pop a line out of the extra lines array
 * 
 * @note
 * Internal function for use in the readline loop(?)
 * should probably move this to a different header as it is internal
 * 
 * @param str string vec to pop from
 * @return char* the next line string
 */
char			*_pop_line(char ***str);

// this one doesnt expand vars
char			*rem_quotes(const char *str);

// this one does expand vars. Not handling $'...'
char			*rmv_quotes_xpnd_var(char *str, t_minishell *shell);
// they should be renamed but i dont want to mess anything up

/*
Env Var helper functions:

There are two variables being tracked, the first is the ACTUAL environment
variables this env is passed to children as well as accessible through
variable expansion.

The second is the internal variables, these are tracked by the shell but only
accessible to the shell and not handed to the child processes.
*/
// TODO: comment this
ssize_t			_sgetanon(char **anon, const char *name);
// TODO: comment this
ssize_t			_sgetidx(char **anon, const char *name);

/**
 * @brief get an environment variable from the internal tracked environment
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
char			*s_get_env(t_minishell *shell, const char *name);

/**
 * @brief get the index of a variable in the internal tracked environment
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
ssize_t			s_get_envid(t_minishell *shell, const char *name);

/**
 * @brief get an shell local variable from the internal tracked variables
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
char			*s_get_interalenv(t_minishell *shell, const char *name);

/**
 * @brief get the index of a shell local variable from the internal tracked vars
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
ssize_t			s_get_internalenvid(t_minishell *shell, const char *name);

/**
 * @brief get a env var from either internal or environment
 * 
 * @param shell shell lol
 * @param name name of var
 * @return char* a string lol
 */
char			*s_get_envany(t_minishell *shell, const char *name);

/**
 * @brief get an ENV string from the shell's environment
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return char* the env string from the environment
 */
char			*s_get_fromthis_env(char **env, const char *name);

/**
 * @brief Sets a variable and value to envp
 * 
 * @param shell the shell struct
 * @param value the value of var
 * @param var	the variable to set with value separated by '='
 * @param envp	a pointer to the environment to set the variable to
 * @return char* the env string from the environment
 */
void			_set_var_value(t_minishell *shell,
					const char *value,
					const char *var, char ***envp);

/*
Things that can be accessed externally in the builtins are
*/

/**
 * @brief typedef for the builtin command definitions
 * 
 * @note
 * builtin functions should not be run under a fork because they need 
 * access to the current state of the shell, this can be proven by running
 * the following:
 * 
 * ```bash
 * export TESTLOL=3 & sleep 2 && echo $TESTLOL
 * ```
 * or
 * ```bash
 * export TESTLOL=2 &
 * env | grep TEST
 * ```
 * 
 * @param shell the shell struct
 * @param argv the arguments passed to the function
 * @param envp the current environment variables
 * @return int the statuscode
 */
typedef int					(*t_builtincmd)(t_minishell *, char **, char ***);

/**
 * @brief Get a builtin command object
 * 
 * these are the only valid strs (others return NULL):
 * ```
 * - echo
 * - env
 * - ~
 * - export
 * - pwd
 * - unset
 * ```
 * 
 * @param str string to check for a builtin command
 * @return t_builtincmd a function to run as a command
 */
t_builtincmd	_get_builtincmd(t_astnode *node);

/**
 * @brief Execute a bultin command
 * 
 * @param shell Reference to the shell
 * @param node Reference to the ast node that calls this
 * @param cmd The builtin function ptr
 * @return int 0?
 */
int				exec_builtincmd(t_minishell *shell,
					t_astnode *node, t_builtincmd cmd);

/**
 * @warning Assumes p is a string, for use in arriter
 * @brief print the string p and return it
 * 
 * @param p a string
 * @return void* same string
 */
void			*print_and_ret(void *p);

/**
 * @warning assumes p is a str (for use in arriter)
 * @brief print a string with export syntax
 * 
 * @param p a string
 * @return void* the same string
 */
void			*export_print_and_ret(void *p);

/**
 * @brief is current directory a git directory
 * 
 * @return int 1 if is git directory
 */
int				is_git_dir(void);

/**
 * @brief user has git installed at /usr/bin/git
 * 
 * @return int 1 if user has git
 */
int				has_git(void);

/**
 * @brief generic run a git command
 * 
 * @param argv args to pass to git command
 * @return char* output of git command
 */
char			*run_git_command(const char **argv);

/**
 * @brief git work tree is dirty
 * 
 * @return int 1 if the git tree is dirty
 */
int				is_git_dirty(void);

/**
 * @brief Restore signals to what they were before the shell init process
 * 
 * @param shell Pointer to the shell
 */
void			restore_signals(const t_minishell *shell);

/**
 * @brief sets the global signal int to be sig
 * 
 * @param sig signal
 * @param info info about signal
 * @param context context for signal
 */
void			default_sig_handle(int sig, siginfo_t *info, void *context);

/**
 * @brief Get the my pid
 * 
 * @return pid_t pid or -1 for error
 */
pid_t			get_my_pid(void);

void			prep_rd_restore(t_redirect_desc *desc);
void			rd_restore(t_redirect_desc *desc);

/**
 * @brief Get redirects ready before execution
 * 
 * @param node 
 * @return int 
 */
int				prepare_fds(t_minishell *shell, t_astnode *node);

/**
 * @brief map fds from fd map
 * 
 * @param node node containing redirect list
 */
int			map_fds(t_astnode *node);

/**
 * @brief unset some signal handlers for execution
 * 
 * @note 
 * this is not a great way to do this, ideally we would just
 * use a process group for the child process and set that as the main
 * process group for the terminal so that minishell doesn't recieve the signal
 * but in order to do that we would need to manage our own process groups
 * and jobs using functions we dont have access too -_-
 */
void			set_exection_signals(void);

/**
 * @brief Set the up signal handlers 
 * 
 * @note
 * this should not be globally accessible in an ideal world
 * but we are constrained and so this does actually need to
 * be called multiple times (unfortunatly)
 * 
 * @param shell the shell 
 * @return int status code -1 on err
 */
int				setup_signals(t_minishell *shell);

/**
 * @brief Check node for variables that might need to be globbed
 * @param node the node to check for globbing
 */
ssize_t			glob_variable(t_astnode	*node);

/**
 * @brief Split on each newline of the string
 * @param str string to split
 * @param data the readline loop internals
 * @returns the split string
 */
char			**simple_split(const char *str, t_readline_data *data);

/**
 * @brief free everything
 * @param shell reference to the shell
 * @param code return code to return
 * @returns code 
 */
int				free_everything(t_minishell *shell, int code);

/**
 * @brief check if the string either doesnt contain a newline
 * or if the string does but the newline is not at the end of the string
 * @note added to remove duplication
 * @param str the string to check
 */
int				last_newline_not_end(const char *str);

/**
 * @brief Expand a variable name, this includes all environments
 * AND special variables
 * @param shell the shell struct
 * @param name the name of the variable to expand
 * @param flag 1 if you want to care about quotes else 0
 */
char			**expand_and_split(t_minishell *shell,
					const char *value, int flag);

void			clean_shell(t_minishell *shell);
void			clean_exit_status(t_minishell *shell, int status);
// TODO: check if correct clean up everything and ~
void			perror_exit(t_minishell *shell, char *message);
void			_free_arr_perror_exit(t_minishell *shell,
					void **arr, char *message);
void			_set_returncode(int *to_set, int code);

/**
 * @brief Join two arrays
 * @param arr1 Left array
 * @param arr2 Right array
 * @returns New allocated array of the joined arrays
 */
void			*arrjoin(void **arr1, void **arr2);

#endif
