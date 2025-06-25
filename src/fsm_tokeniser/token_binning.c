/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/25 14:49:05 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

/*
Would it be better to have some form of 
lookup to allow us to expand this in more meaningful ways
not sure -_-
*/

t_tokentype	potential_redirect(const char *raw_token)
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
	if (raw_token[i] == '<' && (!raw_token[i + 1] || (raw_token[i + 1] == '-' && !raw_token[i + 2])))
		return (TOK_HEREDOC);
	if (raw_token[i] == '&' && ft_isdigit(raw_token[i + 1]))
	{
		i++;
		while (ft_isdigit(raw_token[i]))
			i++;
		if (!raw_token[i])
			return (TOK_REDIR_FD);
	}
	return (TOK_NONE);
}

t_tokentype	bin_token(const char *raw_token)
{
	if (!raw_token)
		return (TOK_NONE);
	if (!*raw_token)
		return (TOK_EOF);
	if (*raw_token == '\'' || *raw_token == '"')
		return (TOK_WORD);
	if (*raw_token == '|')
		return (TOK_PIPE + (7 * (raw_token[1]
					&& raw_token[1] == raw_token[0])));
	if (ft_isdigit(*raw_token) || *raw_token == '>' || *raw_token == '<' )
		return (potential_redirect(raw_token));
	if (*raw_token == ';')
		return (TOK_AFTER);
	if (*raw_token == '&' && raw_token[1] != '>')
		return (TOK_AMP - (4 * (raw_token[1]
					&& raw_token[0] == raw_token[1])));
	if (*raw_token == '&' && raw_token[1] == '>')
		return (TOK_REDIR_OUT + (1 * (raw_token[1] == raw_token[2])));
	if (*raw_token == '(' || *raw_token == ')')
		return (TOK_LPAREN + (*raw_token == ')'));
	return (TOK_WORD);
}

t_tokentype	tokenise_type(t_tokint *tokeniser, const char *str)
{
	char	*substring;

	substring = ft_substr(str, tokeniser->index_start,
			tokeniser->index_end - tokeniser->index_start);
	tokeniser->current_type = bin_token(substring);
	tokeniser->current_token = ft_calloc(1, sizeof(t_token));
	(*tokeniser->current_token) = (t_token){.heredoc_delim = 0,
		.raw = substring, .type = tokeniser->current_type,};
	if (tokeniser->current_type == TOK_WORD && tokeniser->previous_line)
	{
		ft_dirtyswap((void *)&tokeniser->current_token->raw,
			ft_strjoin(tokeniser->previous_line, substring), free);
		ft_dirtyswap((void *)&tokeniser->previous_line, 0, free);
	}
	return (tokeniser->current_type);
}
