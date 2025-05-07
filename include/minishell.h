/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/07 10:34:36 by hbreeze          ###   ########.fr       */
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
# include "./input_tokens.h"
# include "./abstract_syntax_tree.h"

typedef struct s_minishell	t_minishell;
struct s_minishell
{
	char		**environment;
	t_list		*tokens;
	t_token		**tokenv;
	t_astnode	*current_tree;

	/*
	i think the best way to handle this would be to keep concatinating
	the readlines until we reach the point where we have a valid AST.

	then append the history item.

	then run the execution tree.
	*/
	char		*current_line; // this is everything we have read for the current pipeline.
	char		*current_pipeline; // this is everything we are tokenising and running
	char		**extra_lines; // this is every line that we are not currently tokenising

	char		*prompt;
};

int	readline_loop(t_minishell *shell);

void	print_token_list(t_list *list);// TODO: remove this when we dont need to bebug it anymore?

void	free_all_tokens(t_minishell *shell, void (*del_raw)(void *), void (*del_str)(void *));
#endif
