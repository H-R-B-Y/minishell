/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_binning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 17:14:33 by hbreeze          ###   ########.fr       */
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
	if (raw_token[i] == '<' && (!raw_token[i + 1]
			|| (raw_token[i + 1] == '-' && !raw_token[i + 2])))
		return (TOK_HEREDOC);
	if (raw_token[i] == '&' && ++i)
		return (_p_redirect_amp(raw_token, i));
	return (TOK_WORD);
}

/*
I HATE this

Maybe it could be done using a static map,
loop through the map and each one defines a token type to produce?

idk, probably too late to rewrite this though

NOTE: lol i already commented this above LOL
*/
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

static int	unfinished_string_check(t_tokint *tokeniser, const char *str)
{
	if (tokeniser->quote_mode != QUOTE_NONE || (tokeniser->i_end > 1
			&& str[tokeniser->i_end - 1] == '\\'
			&& str[tokeniser->i_end - 2] != '\\'))
		return (1);
	return (0);
}

t_tokentype	tokenise_type(t_tokint *tokeniser, const char *str)
{
	char	*substring;

	if (unfinished_string_check(tokeniser, str))
		return ((int [2]){TOK_INCOMPLETE_STRING, TOK_ERR}
			[!handle_unclosed_quote(tokeniser, str)]);
	substring = ft_substr(str, tokeniser->i_start,
			tokeniser->i_end - tokeniser->i_start);
	tokeniser->curr_type = bin_token(substring);
	tokeniser->curr_token = ft_calloc(1, sizeof(t_token));
	if (!substring || !tokeniser->curr_token)
		return (TOK_ERR);
	(*tokeniser->curr_token) = (t_token){.heredoc_delim = 0,
		.raw = substring, .type = tokeniser->curr_type,};
	if (!(tokeniser->curr_type == TOK_WORD && tokeniser->prev_line))
		return (tokeniser->curr_type);
	if (last_newline_not_end(tokeniser->prev_line))
		ft_dirtyswap((void *)&tokeniser->curr_token->raw, str_vec_join(
				(char *[4]){tokeniser->prev_line, "\n", substring, 0}), free);
	else
		ft_dirtyswap((void *)&tokeniser->curr_token->raw,
			str_vec_join((char *[3]){tokeniser->prev_line, substring, 0}),
			free);
	ft_dirtyswap((void *)&tokeniser->prev_line, 0, free);
	return (tokeniser->curr_type);
}
