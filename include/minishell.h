/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/31 17:19:24 by cquinter         ###   ########.fr       */
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
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <term.h>

# include "./libft.h"
# include "./fsm_tokeniser.h"
# include "./readline_loop.h"
# include "./abstract_syntax_tree.h"
# include "./execution.h"
# include "./builtin.h"

/**
 * @brief the main struct for storing minishell state
 * @param environment placeholder for when we store environment
 * @param tokens a linked list of tokens created from the lexar
 * @param tokenv a vector array of tokens (null terminated)
 * @param current_tree the current AST tree produced from the tokens
 * @param current_line the current line to add to history
 * @param current_pipeline the current command string we are running
 * @param extra_lines a vector array of extra lines read from readline
 * 
 * @note extra lines should not be populated after readline loop
 * (it should be free'd)
 * @param prompt I thought it would be nice if we allowed the prompt 
 * to be customised so i made it a variable, should probably indicate current
 * directory too.
 */
typedef struct s_minishell	t_minishell;
struct s_minishell
{
	/*
	this is the environment that will be passed down to any child process
	at the start of the program we take a copy of the environment varaiables
	so that we can edit them on the fly.
	*/
	char		**environment;

	/*
	this is another environment variable array, this one however 
	is only in the context of the current shell, it can be used for variable
	expansion but cannot be passed to child processes.
	*/
	char		**local_env;

	/*
	tokens list is just for the internal tokenisation process, it probably
	shouldnt be included as part of the main struct! ~ i can remove this later
	*/
	t_list		*tokens;

	/*
	token vector is part of the main struct solely as a reference for cleaning up
	all the tokens need to be kept for the entire execution process
	(well only until they are executed i guess)
	but if this reference to them here this is all we need to cleanup
	*/
	t_token		**tokenv;

	/*
	current tree, nodes will need to be free'd but their internal tokens
	do not have to be free'd
	*/
	t_astnode	*current_tree;

	/*
	internal finite state machine data*/
	t_fsmdata	fsm_data;

	t_readline_data	rldata;
	/*
	i think the best way to handle this would be to keep concatinating
	the readlines until we reach the point where we have a valid AST.

	then append the history item.

	then run the execution tree.
	*/
	// this is everything we have read for the current pipeline.
	char		*current_line;
	// this is everything we are tokenising and running
	char		*current_pipeline;
	// this is every line that we are not currently tokenising
	char		**extra_lines;

	char		*prompt;
};

/**
 * @brief readline and create token list
 * @param shell the shell struct
 * @return 1 if eof 0 if successful?
 * 
 * Function will populate:
 * - current_line
 * - current_pipeline
 * - extra_lines
 * 
 * It should probably updated to return some kind of information about why
 * it returned
 * TODO: make an enum for return codes so we can tell why it returned? 
 */
int				readline_loop(t_minishell *shell);

/**
 * @brief print out a token list in columns
 * @param list the list of tokens to print
 * 
 * TODO: this should probably be moved to the input tokens header.
 */
void			print_token_list(t_list *list);

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
char			*str_join_with_sep(char *str1, char *str2, char *sep);

/**
 * @brief join together a null terminated array of strings
 * 
 * @param arr a null terminated array of strings
 * @return char* joined string
 */
char			*str_vec_join(char **arr);
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


char	*remove_quotes(char *str);


int	read_until_complete_command(t_minishell *shell);

t_redirect_desc	*handle_heredoc(t_minishell *shell, char *delim);

/*
Env Var helper functions:

There are two variables being tracked, the first is the ACTUAL environment
variables this env is passed to children as well as accessible through
variable expansion.

The second is the internal variables, these are tracked by the shell but only
accessible to the shell and not handed to the child processes.
*/

ssize_t			_sgetanon(char **anon, char *name);

/**
 * @brief get an environment variable from the internal tracked environment
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
char			*s_get_env(t_minishell *shell, char *name);

/**
 * @brief get the index of a variable in the internal tracked environment
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
ssize_t			s_get_envid(t_minishell *shell, char *name);

/**
 * @brief get an shell local variable from the internal tracked variables
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
char			*s_get_interalenv(t_minishell *shell, char *name);

/**
 * @brief get the index of a shell local variable from the internal tracked vars
 * 
 * @param shell the shell object
 * @param name the name of the variable
 * @return char* the entire variable entry
 */
ssize_t			s_get_internalenvid(t_minishell *shell, char *name);

/**
 * @brief get a env var from either internal or environment
 * 
 * @param shell shell lol
 * @param name name of var
 * @return char* a string lol
 */
char	*s_get_envany(t_minishell *shell, char *name);

/**
 * @brief get an ENV string from the shell's environment
 * 
 * @param shell the shell struct
 * @param name the name of the environment variable
 * @return char* the env string from the environment
 */
char 	*s_get_fromthis_env(char **env, char *name);

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
typedef int					(*t_builtincmd)(t_minishell *, char **, char **);


/**
 * @brief Get a builtin command object
 * 
 * these are the only valid strs (others return NULL):
 * ```
 * - echo
 * - env
 * - exit
 * - export
 * - pwd
 * - unset
 * ```
 * 
 * @param str string to check for a builtin command
 * @return t_builtincmd a function to run as a command
 */
int	get_run_builtincmd(t_minishell *shell);

void	*print_and_ret(void *p);



#endif
