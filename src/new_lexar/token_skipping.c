/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_skipping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:12:14 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/11 12:12:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isoperator(char c);

size_t	skip_quoted(char *str, size_t i)
{
	size_t	start;
	char	quote;

	quote = str[i];
	start = i;
	i++;
	while (str[i] && (str[i] != quote
			|| (str[i] == quote && i > 1
			&& str[i - 1] == '\\' && quote == '"')))//TODO: double quote can be escaped
		i++;
	if (str[i])
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

size_t	skip_word(char *str, size_t i)
{
	size_t	start;

	start = i;
	while (str[i] && !ft_iswhitespace(str[i]) && !isoperator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quoted(str, i);
		else if (str[i] == '\\' && (ft_iswhitespace(str[i + 1])
				|| isoperator(str[i + 1])
				|| ft_strchr("\\\"'", str[i + 1]))) // TODO: check that single quotes cannot be escaped.
			i += 2;
		else
			i++;
	}
	return (i - start);
}

