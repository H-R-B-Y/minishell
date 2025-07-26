/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:29 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/26 17:55:06 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_LOOP_H
# define READLINE_LOOP_H

# include "libft.h"

typedef struct s_minishell	t_minishell;

typedef enum e_readline_retcode	t_readline_retcode;
enum e_readline_retcode
{
	READ_START,
	READ_OK,
	READ_NOTHING,
	READ_EOF,
	READ_ERROR,
	READ_BADPARSE,
	READ_FATAL,
	READ_RETCODE_COUNT
};

typedef struct s_readline_data	t_readline_data;
struct s_readline_data
{
	char				**extra_lines;
	size_t				extra_line_count;
	char				*current_hist_item;
	char				*last_line;
	short int			*interactive_mode;
};

ssize_t	split_extra_lines(t_readline_data *data, char *str);

int		next_line(t_readline_data *data, const char *prompt);

char	*_pop_line(char ***arr);

int		read_until_complete_command(t_minishell *shell);

ssize_t	append_to_history_item(t_readline_data *data, char **str);

void	append_tokenv_to_history_item(t_minishell *shell, t_readline_data *rl_data, t_list *tokens);

char	*readline_wrapper(t_readline_data *data, const char *prompt);

#endif
