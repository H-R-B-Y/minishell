/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:12:14 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 11:34:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isoperator(char c);
int	quote_closed(char *str, size_t i, char quote);

size_t	skip_quoted(char *str, size_t i, char quote)
{
	size_t	start;

	start = i;
	while (str[i] && !quote_closed(str, i, quote))//TODO: double quote can be escaped
		i++;
	return (i - start);
}

size_t	skip_potential_double(char *str, size_t i)
{
	size_t	start;

	start = i;
	if (++i && str[i] == str[i - 1])
		i++;
	return (i - start);
}



size_t	_skip_quoted_internal(t_tokeniserinternal *meta, char *str, size_t i, char quote)
{
	size_t	start;

	start = i;
	if (str[i] != quote)
	{
		i += skip_quoted(str, i + 1, quote) + 1;
		if (quote_closed(str, i, quote))
		{
			quote = 0;
			if (meta->parse_stack
				&& (LCONT == EXPECT_DQUOTE || LCONT == EXPECT_QUOTE))
				POPCONT ;
		}
		i++;
	}
	else if (++i && meta->parse_stack && (LCONT == EXPECT_DQUOTE || LCONT == EXPECT_QUOTE))
		POPCONT ;
	return (i - start);
}

size_t	skip_word(t_tokeniserinternal *meta, char *str, size_t i, char quote)
{
	size_t	start;

	start = i;
	while (str[i] && ((!ft_iswhitespace(str[i]) && !isoperator(str[i])) || quote))
	{
		if (quote)
		{
			i += _skip_quoted_internal(meta, str, i, quote);
			quote = quote * (!quote_closed(str, i -1, quote));
		}
		else if (str[i] == '\'' || (str[i] == '"' && ((i > 0 && str[i - 1] != '\\') || i == 0)))
		{
			ft_lstadd_back(&meta->parse_stack, ft_lstnew(ETOPTR EXPECT_QUOTE + (1 * (str[i] == '"'))));
			i += _skip_quoted_internal(meta, str, i + 1, str[i]) + 1;
		}
		else if (str[i] == '\\' && (ft_iswhitespace(str[i + 1])
				|| isoperator(str[i + 1]) || str[i+1] == '\n'
				|| ft_strchr("\\\"'", str[i + 1]))) // TODO: check that single quotes cannot be escaped.
			i += 2;
		else
			i++;
	}
	return (i - start);
}

