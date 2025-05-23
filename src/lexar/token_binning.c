/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:39:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:18:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokentype	bin_token(const char *raw_token)
{
	if (!raw_token)
		return (TOK_NONE);
	if (!*raw_token)
		return (TOK_END);
	if (*raw_token == '\'' || *raw_token == '"')
		return (TOK_WORD);
	if (*raw_token == '|')
	{
		if (raw_token[1] && raw_token[1] == raw_token[0])
			return (TOK_OR_IF);
		return (TOK_PIPE);
	}
	if (*raw_token == '>' || *raw_token == '<')
	{
		if (raw_token[1] && raw_token[0] == raw_token[1])
			return (TOK_REDIR_APPEND + (2 * (raw_token[0] == '<')));
		return (TOK_REDIR_OUT + (2 * (raw_token[0] == '<')));
	}
	if (*raw_token == ';')
		return (TOK_AFTER);
	if (*raw_token == '&')
	{
		if (raw_token[1] && raw_token[0] == raw_token[1])
			return (TOK_AND_IF);
		return (TOK_AMP);
	}
	if (*raw_token == '(' || *raw_token == ')')
		return (TOK_LPAREN + (*raw_token == ')'));
	return (TOK_WORD);
}

t_list	*bin_and_create_token(char *raw_token)
{
	t_list		*output;
	t_token		*tok;
	t_tokentype	type;

	if (!raw_token)
		return ((void *)0);
	type = bin_token(raw_token);
	if (type == TOK_NONE)
		return ((void *)0);
	tok = create_token(type, raw_token);
	if (!tok)
		return ((void *)0);
	output = ft_lstnew(tok);
	if (!output)
		return ((void *)0);
	return (output);
}
