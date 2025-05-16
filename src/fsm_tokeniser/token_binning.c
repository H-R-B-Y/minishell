/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 11:20:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

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
	if (*raw_token == '>' || *raw_token == '<')
		return (TOK_REDIR_OUT + (2 * (raw_token[0] == '<'))
			+ (raw_token[1] && raw_token[0] == raw_token[1]));
	if (*raw_token == ';')
		return (TOK_AFTER);
	if (*raw_token == '&')
		return (TOK_AMP - (4 * (raw_token[1]
			&& raw_token[0] == raw_token[1])));
	if (*raw_token == '(' || *raw_token == ')')
		return (TOK_LPAREN + (*raw_token == ')'));
	return (TOK_WORD);
}

t_tokentype	tokenise_type(t_tokint *tokeniser, char *str)
{
	char *substring;

	substring = ft_substr(str, tokeniser->index_start,
		tokeniser->index_end - tokeniser->index_start);
	tokeniser->current_type = bin_token(substring);
	tokeniser->current_token = ft_calloc(1, sizeof(t_token));
	(*tokeniser->current_token) = (t_token){.heredoc_delim = 0,
		.raw = substring, .type = tokeniser->current_type,};
	if (tokeniser->current_type == TOK_WORD && tokeniser->previous_line)
	{
		substring = ft_strjoin(tokeniser->previous_line, substring);
		free(tokeniser->current_token->raw);
		tokeniser->current_token->raw = substring;
		free(tokeniser->previous_line);
		tokeniser->previous_line = 0;
	}
	return (tokeniser->current_type);
}
