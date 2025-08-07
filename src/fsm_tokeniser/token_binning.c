/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 12:35:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Would it be better to have some form of 
lookup to allow us to expand this in more meaningful ways
not sure -_-
*/

static t_tokentype	_p_redirect_amp(const char *raw_token, int i)
{
	while (ft_iswhitespace(raw_token[i]))
		i++;
	if (!(ft_isdigit(raw_token[i]) || raw_token[i] == '-'))
		return (TOK_WORD);
	i++;
	if (raw_token[i - 1] != '-')
		while (ft_isdigit(raw_token[i]))
			i++;
	if (!raw_token[i])
		return (TOK_REDIR_FD);
	return (TOK_WORD);
}

static t_tokentype	potential_redirect(const char *raw_token)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(raw_token[i]))
		i++;
	if (!(raw_token[i] == '>' || raw_token[i] == '<'))
		return (TOK_WORD);
	if (!raw_token[i + 1])
		return (TOK_REDIR_OUT + (2 * (raw_token[i] == '<')));
	i++;
	if (raw_token[i] == '>' && !raw_token[i + 1])
		return (TOK_REDIR_APPEND);
	if (raw_token[i] == '<' && (!raw_token[i + 1]
			|| (raw_token[i + 1] == '-' && !raw_token[i + 2])))
		return (TOK_HEREDOC);
	if (raw_token[i] == '&' && ++i)
		return (_p_redirect_amp(raw_token, i));
	return (TOK_WORD);
}

static t_tokentype	bin_pipe_condition_redr(const char *raw_token)
{
	if (*raw_token == '|')
	{
		if (raw_token[0] == raw_token[1])
			return (TOK_OR_IF);
		return (TOK_PIPE);
	}
	if (*raw_token == '&')
	{
		if (raw_token[1] == '>')
		{
			if (raw_token[2] == '>')
				return (TOK_REDIR_APPEND);
			return (TOK_REDIR_OUT);
		}
		else if (raw_token[0] == raw_token[1])
			return (TOK_AND_IF);
		return (TOK_AMP);
	}
	return (TOK_WORD);
}

t_tokentype	bin_token(const char *raw_token)
{
	if (!raw_token)
		return (TOK_NONE);
	if (!*raw_token)
		return (TOK_EOF);
	if (*raw_token == '\'' || *raw_token == '"')
		return (TOK_WORD);
	if (raw_token[0] == '(')
		return (TOK_LPAREN);
	if (raw_token[0] == ')')
		return (TOK_RPAREN);
	if (*raw_token == ';')
		return (TOK_AFTER);
	if (ft_isdigit(*raw_token) || *raw_token == '>' || *raw_token == '<')
		return (potential_redirect(raw_token));
	return (bin_pipe_condition_redr(raw_token));
}
