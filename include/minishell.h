/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 17:30:17 by hbreeze          ###   ########.fr       */
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
// # include "./input_tokens.h"
// # include "./new_lexar.h"
# include "./fsm_tokeniser.h"
# include "./readline_loop.h"
# include "./abstract_syntax_tree.h"

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
	char		**environment;
	t_list		*tokens;
	t_token		**tokenv;
	t_astnode	*current_tree;

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
int		readline_loop(t_minishell *shell);

/**
 * @brief print out a token list in columns
 * @param list the list of tokens to print
 * 
 * TODO: this should probably be moved to the input tokens header.
 */
void	print_token_list(t_list *list);

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
char	*str_join_with_sep(char *str1, char *str2, char *sep);

char	*str_vec_join(char **arr);


void readline_cleanup(t_minishell *shell);

int	read_until_complete_command(t_minishell *shell);

#endif
