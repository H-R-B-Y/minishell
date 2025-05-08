/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:52:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 15:01:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void readline_cleanup(void)
{
	return ;
}

char	*join_with_sep(char *str1, char *str2, char *sep)
{
	char	*out;
	size_t	lengths[3];

	if (!str1 || !str2 || !sep)
		return ((void *)0);
	lengths[0] = ft_strlen(str1);
	lengths[1] = ft_strlen(str2);
	lengths[2] = ft_strlen(sep);
	out = malloc(sizeof(char) * (lengths[0] + lengths[1] + lengths[2] + 1));
	if (!out)
		return ((void *)0);
	out[lengths[0] + lengths[1] + lengths[2]] = '\0';
	ft_memmove(out, str1, lengths[0]);
	ft_memmove(out + lengths[0], sep, lengths[2]);
	ft_memmove(out + lengths[0] + lengths[2], str2, lengths[1]);
	return (out);
}

char *_pop_line(t_minishell *shell)
{
	char	*str;

	str = shell->extra_lines[0];
	ft_memmove(shell->extra_lines, &shell->extra_lines[1],
		(ft_arrlen((void *)&shell->extra_lines[1]) + 1) * sizeof(char *));
	return (str);
}

char *readline_handle_multiline(t_minishell *shell, char *new_line)
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
		str = readline(prompt);
		extra_line = join_with_sep(shell->current_line, str, "\n");
		free(shell->current_line);
		shell->current_line = extra_line;
		if (!str || !*str)
			return (0); // this doesnt need to distinquish between as SIGINT and EOF it will be handled in the readline loop.
		else if (ft_strchr(str, '\n'))
			return (readline_handle_multiline(shell, str));
		return (str);
	}
}



int	tokenise_and_validate(t_minishell *shell)
{
	t_tokerr	err;
	char		*buff[3];

	shell->tokens = tokenise(shell->current_pipeline);
	err = cleanse_validate_tokens(shell->tokens);
	while (err)
	{
		free_token_list(shell->tokens, free, free);
		buff[0] = readline_subloop(shell, (void *)token_err_type_to_string(err));
		if (buff[0])
		{
			if (ft_strchr(buff[0], '\n'))
			{
				buff[2] = readline_handle_multiline(shell, buff[0]);
				free(buff[0]);
				if (!buff[2])
					return (1);
			}
			buff[1] = join_with_sep(shell->current_pipeline, buff[0], "");
			free(shell->current_pipeline);
			shell->current_pipeline = buff[1];
			free(buff[0]);
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
	{
		if (errno == EINTR)
			return (readline_cleanup(), 0);
		else
			return (readline_cleanup(), 1);
	}
	if (ft_strchr(shell->current_line, '\n'))
		shell->current_pipeline = readline_handle_multiline(shell, shell->current_line);
	else
		shell->current_pipeline = ft_strdup(shell->current_line);
	if (tokenise_and_validate(shell))
	{
		if (errno == EINTR)
			return (readline_cleanup(), 0);
		return (1);
	}
	// I am thinking that once we get a valid token list here we can exit this function and handle
	// the AST construcion outside in the main?
	print_token_list(shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	shell->current_tree = produce_ast(shell->tokenv, ft_arrlen((void *)shell->tokenv));
	print_ast(shell->current_tree, "|	|");
	add_history(shell->current_line);
	return (readline_cleanup(), 0);
}


