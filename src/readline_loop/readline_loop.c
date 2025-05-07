/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:52:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/07 10:53:05 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void readline_cleanup(void)
{
	return ;
}


void readline_handle_multiline(t_minishell *shell, char *new_line)
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
		return ;
	ft_memmove(temp, shell->extra_lines, lengths[0] * sizeof(char *));
	ft_memmove(temp + lengths[0], newlines, lengths[1] * sizeof(char *));
	ft_arrclear((void *)shell->extra_lines, 0);
	ft_arrclear((void *)newlines, 0);
	shell->extra_lines = temp;
}


/*
Function to be called when we need to expect more input from the user
within the prompt.

i.e. when unclosed parenthesis or unclosed quotes
*/
char	*readline_subloop(t_minishell *shell, char *prompt)
{
	char	*str;
	// size_t	len;

	if (shell->extra_lines && *shell->extra_lines)
	{
		// len = ft_arrlen((void *)shell->extra_lines);
		str = ft_strdup(shell->extra_lines[0]);
		free(shell->extra_lines[0]);
		ft_memmove(shell->extra_lines, &shell->extra_lines[1],
			(ft_arrlen((void *)&shell->extra_lines[1]) + 1) * sizeof(char *));
		return (str);
	}
	else
	{
		str = readline(prompt);
		// if newline in the extra lines here then they need to be appended to the extra lines in the shell
		return (str);
	}
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
			buff[1] = join_with_sep(shell->current_line, buff[0], "\n");
			free(shell->current_line);
			shell->current_line = buff[1];
			if (ft_strchr(buff[0], '\n'))
			{
				readline_handle_multiline(shell, buff[0]);
				free(buff[0]);
				buff[0] = readline_subloop(shell, "");
				if (!buff[0])
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

/*
Note: there is alot that needs to happen before we acutally begin to read lines, such as:
- get envp
- test if we are a tty 
- setup signal handlers

some optional stuff that i would love to try and do would be to add the current git repo to the prompt, but
we can see how feasible that is down the line.
*/



/*
we need to be able to run this in a loop
we need to return something, perhaps a status code?

keep it as int for now, can be re-written later if we need to return something else;
*/
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
	{
		readline_handle_multiline(shell, shell->current_line);
		shell->current_pipeline = readline_subloop(shell, "");
	}
	else
		shell->current_pipeline = ft_strdup(shell->current_line);
	if (tokenise_and_validate(shell))
		if (errno == EINTR)
			return (readline_cleanup(), 0);
	print_token_list(shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	shell->current_tree = produce_ast(shell->tokenv, ft_arrlen((void *)shell->tokenv));
	print_ast(shell->current_tree, "|	|");
	return (readline_cleanup(), 0);
}


