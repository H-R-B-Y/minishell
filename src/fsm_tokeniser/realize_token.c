/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realize_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:55:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/19 21:30:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	isescaped(const char *str, size_t i_end)
{
	size_t	count;
	ssize_t	idx;

	count = 0;
	idx = i_end;
	if (str[i_end] == '\n')
		idx--;
	while (idx >= 0 && str[idx] == '\\')
	{
		idx--;
		count++;
	}
	if (count % 2)
		return (1);
	return (0);
}

static int	unfinished_string_check(t_tokint *tokeniser, const char *str)
{
	if (tokeniser->quote_mode != QUOTE_NONE
		|| (tokeniser->i_end > 0
			&& (str[tokeniser->i_end - 1] == '\\'
				|| (tokeniser->i_end > 1 && str[tokeniser->i_end - 2 == '\\']
					&& str[tokeniser->i_end - 1] == '\n'))
			&& isescaped(str, tokeniser->i_end - 1)))
		return (1);
	return (0);
}

t_tokentype	_create_token(t_tokint *tokeniser, const char *str)
{
	char	*substring;

	substring = ft_substr(str, tokeniser->i_start,
			tokeniser->i_end - tokeniser->i_start);
	tokeniser->curr_type = bin_token(substring);
	tokeniser->curr_token = ft_calloc(1, sizeof(t_token));
	if (!substring || !tokeniser->curr_token)
		return (TOK_ERR);
	(*tokeniser->curr_token) = (t_token){.raw = substring,
		.type = tokeniser->curr_type,};
	return (tokeniser->curr_type);
}

int	_handle_continuation(t_tokint *tokeniser)
{
	char	*new_value;

	if (last_newline_not_end(tokeniser->prev_line))
		new_value = str_vec_join(
				(const char *[4]){tokeniser->prev_line, "\n",
				tokeniser->curr_token->raw, 0});
	else
		new_value = ft_strjoin(tokeniser->prev_line,
				tokeniser->curr_token->raw);
	if (!new_value)
		return (-1);
	ft_dirtyswap((void *)&tokeniser->prev_line, 0, free);
	ft_dirtyswap((void *)&tokeniser->curr_token->raw, new_value, free);
	if (tokeniser->curr_token->type != TOK_WORD)
	{
		tokeniser->curr_token->type = TOK_WORD;
		tokeniser->curr_type = TOK_WORD;
	}
	return (1);
}

t_tokentype	realize_token(t_tokint *tokeniser, const char *str)
{
	if (unfinished_string_check(tokeniser, str))
		return ((int [2]){TOK_INCOMPLETE_STRING, TOK_ERR}
			[!handle_unclosed_quote(tokeniser, str)]);
	if (_create_token(tokeniser, str) == TOK_ERR)
		return (TOK_ERR);
	if (!(tokeniser->prev_line))
		return (tokeniser->curr_type);
	if (_handle_continuation(tokeniser) < 0)
		return (TOK_ERR);
	return (tokeniser->curr_type);
}
