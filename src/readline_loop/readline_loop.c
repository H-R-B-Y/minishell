/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:52:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 16:32:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*_pop_line(t_minishell *shell);
void	readline_cleanup(void);

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
char	*readline_subloop(t_minishell *shell, char *prompt) // the prompt here doesnt really look right
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
		if (!str || !*str)
			return (0); // this doesnt need to distinquish between as SIGINT and EOF it will be handled in the readline loop.
		else if (ft_strchr(str, '\n'))
			return (readline_handle_multiline(shell, str));
		return (str);
	}
}

int	_cleanup_nextlines(t_minishell *shell, char *buff, t_tokerr err)
{
	char				*temp[3];
	static const char	*err_join[TOKEN_ERROR_COUNT]
		= {"", "\n", "\n", "; ", "", "", "", ""}; // TODO: this might need to be moved somewhere else im not sure this will be sufficient if we add more errors.

	if (ft_strchr(buff, '\n'))
	{
		temp[2] = readline_handle_multiline(shell, buff);
		if (!temp[2])
			return (1);
	}
	temp[1] = str_join_with_sep(shell->current_pipeline,
		buff, (void *)err_join[err]);
	free(shell->current_pipeline);
	shell->current_pipeline = temp[1];
	return (0);
}

int	tokenise_and_validate(t_minishell *shell)
{
	t_tokerr	err;
	char		*buff;

	shell->tokens = tokenise(shell->current_pipeline);
	err = cleanse_validate_tokens(shell->tokens);
	while (err) // This needs to be a list of fixable errors
	{
		free_token_list(shell->tokens, free, free);
		buff = readline_subloop(shell, (void *)token_err_type_to_string(err));
		if (buff)
		{
			err = _cleanup_nextlines(shell, buff, err);
			free(buff);
			if (err)
				return (1);
		}
		else
			return (1);
		shell->tokens = tokenise(shell->current_pipeline);
		err = cleanse_validate_tokens(shell->tokens);
	}
	return (0);
}


int	readline_loop(t_minishell *shell)
{
	shell->current_line = readline(shell->prompt);
	if (!shell->current_line || !*shell->current_line)
		return (errno != EINTR);
	if (ft_strchr(shell->current_line, '\n'))
		shell->current_pipeline = readline_handle_multiline(shell, shell->current_line);
	else
		shell->current_pipeline = ft_strdup(shell->current_line);
	if (tokenise_and_validate(shell))
		return (errno != EINTR);
	return (0);
}


