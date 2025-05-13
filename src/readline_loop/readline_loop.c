/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:52:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 18:30:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*_pop_line(t_minishell *shell);
void	readline_cleanup(t_minishell *shell);

char	*readline_handle_multiline(t_minishell *shell, char *new_line)
{
	char	**newlines;
	char	**temp;
	size_t	lengths[2];

	newlines = ft_split(new_line, '\n');
	if (!newlines[1])
		ft_arrclear((void *)newlines, free);
	lengths[0] = ft_arrlen((void *)shell->extra_lines);
	lengths[1] = ft_arrlen((void *)newlines);
	temp = ft_calloc(lengths[0] + lengths[1] + 1, sizeof(char *));
	if (!temp)
		return ((void *)0);
	ft_memmove(temp, shell->extra_lines, lengths[0] * sizeof(char *));
	ft_memmove(temp + lengths[0], newlines, lengths[1] * sizeof(char *));
	ft_arrclear((void *)shell->extra_lines, 0);
	ft_arrclear((void *)newlines, 0);
	shell->extra_lines = temp;
	return (_pop_line(shell));
}


/*
Function to be called when we need to expect more input from the user
within the prompt.

i.e. when unclosed parenthesis or unclosed quotes
*/
char	*readline_subloop(t_minishell *shell, char *prompt)
{
	char	*str;
	char	*extra_line;

	if (shell->extra_lines && *shell->extra_lines)
		return (_pop_line(shell));
	else
	{
		printf("%s", prompt);
		str = readline(" > ");
		extra_line = str_join_with_sep(shell->current_line, str, "\n");
		free(shell->current_line);
		shell->current_line = extra_line;
		if (!str)
			return (0);
		else if (ft_strchr(str, '\n'))
			return (readline_handle_multiline(shell, str));
		return (str);
	}
}

int	tokenise_and_validate(t_minishell *shell)
{
	char		*buff;

	shell->tokens = tokenise(&shell->tok_internal, shell->current_pipeline);
	while (shell->tok_internal.state == PARSE_CONTINUE)
	{
		buff = readline_subloop(shell, "print_error_string_here ? ");
		if (!buff)
			return (1);
		shell->tokens = tokenise(&shell->tok_internal, buff);
	}
	if (shell->tok_internal.state == PARSE_ERROR)
		return (0);
	return (0);
}


int	readline_loop(t_minishell *shell)
{
	readline_cleanup(shell);
	shell->current_line = readline(shell->prompt);
	if (!shell->current_line)
		return (errno != EINTR);
	if (ft_strchr(shell->current_line, '\n'))
		shell->current_pipeline
			= readline_handle_multiline(shell, shell->current_line);
	else
		shell->current_pipeline = ft_strdup(shell->current_line);
	if (tokenise_and_validate(shell))
		return (errno != EINTR);
	return (0);
}


