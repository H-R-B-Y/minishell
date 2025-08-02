/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:42:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 19:44:02 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	skip_token_str(t_tokint *tokeniser, const char *str)
{
	char	c;

	while (str[tokeniser->i_end])
	{
		c = str[tokeniser->i_end];
		if (c == '\\' && tokeniser->quote_mode != QUOTE_SINGLE
			&& str[tokeniser->i_end + 1])
			tokeniser->i_end++;
		else if (tokeniser->quote_mode == QUOTE_DOUBLE && c == '"')
			tokeniser->quote_mode = QUOTE_NONE;
		else if (tokeniser->quote_mode == QUOTE_SINGLE && c == '\'')
			tokeniser->quote_mode = QUOTE_NONE;
		else if (tokeniser->quote_mode == QUOTE_NONE)
		{
			if (c == '\'')
				tokeniser->quote_mode = QUOTE_SINGLE;
			else if (c == '"')
				tokeniser->quote_mode = QUOTE_DOUBLE;
			else if (isoperator(c) || ft_iswhitespace(c) || c == '\0')
				break ;
		}
		tokeniser->i_end++;
	}
}

void	tokeniser_skip_whitespace(t_tokint *tokeniser, const char *str)
{
	if (!str || !*str)
		return ;
	if (tokeniser->curr_type != TOK_INCOMPLETE_STRING)
	{
		while (ft_iswhitespace(str[tokeniser->i_start]))
			tokeniser->i_start++;
	}
	tokeniser->i_end = tokeniser->i_start;
}

t_tokentype	next_token_type(t_tokint *tokeniser, const char *str)
{
	tokeniser->i_start = tokeniser->i_end;
	if (tokeniser->quote_mode == QUOTE_NONE
		&& ft_iswhitespace(str[tokeniser->i_start]))
		tokeniser_skip_whitespace(tokeniser, str);
	if (tokeniser->quote_mode == QUOTE_NONE
		&& (isoperator(str[tokeniser->i_start])
			|| ft_isdigit(str[tokeniser->i_start])))
		handle_operator(tokeniser, str);
	else
		skip_token_str(tokeniser, str);
	return (tokenise_type(tokeniser, str));
}
