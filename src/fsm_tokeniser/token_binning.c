/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 17:36:52 by hbreeze          ###   ########.fr       */
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

t_tokentype	tokenise_type(char *str)
{
	char *substring;

	substring = ft_substr(str, TOKENISER.index_start,
		TOKENISER.index_end - TOKENISER.index_start);
	TOKENISER.current_type = bin_token(substring);
	TOKENISER.current_token = ft_calloc(1, sizeof(t_token));
	(*TOKENISER.current_token) = (t_token){.heredoc_deliminator = 0,
		.raw = substring, .type = TOKENISER.current_type,};
	if (TOKENISER.current_type == TOK_WORD && TOKENISER.previous_line)
	{
		substring = ft_strjoin(TOKENISER.previous_line, substring);
		free(TOKENISER.current_token->raw);
		TOKENISER.current_token->raw = substring;
		free(TOKENISER.previous_line);
		TOKENISER.previous_line = 0;
	}
	return (TOKENISER.current_type);
}
