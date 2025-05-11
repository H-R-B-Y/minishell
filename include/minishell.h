/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:44:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:55:25 by hbreeze          ###   ########.fr       */
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
	char		**extra_lines;
};

#endif
