/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:31:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 21:56:41 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quoted_backslash(const char *str,
	size_t *i, char *output, t_quote_mode mode)
{
	if (ft_strchr("$'\"\\", str[i[0] + 1]))
	{
		if (mode == QUOTE_SINGLE)
			output[i[1]++] = str[i[0]++];
		else
			i[0]++;
		output[i[1]++] = str[i[0]++];
	}
	else
		output[i[1]++] = str[i[0]++];
}

static void	handle_nonquoted(const char *str,
	size_t *i, char *output, t_quote_mode *mode)
{
	if (str[i[0]] == '\'' && ++i[0])
		*mode = QUOTE_SINGLE;
	else if (str[i[0]] == '"' && ++i[0])
		*mode = QUOTE_DOUBLE;
	else if (str[i[0]] == '\\' && str[i[0] + 1] == '\n' && ++i[0])
		i[0]++;
	else if (str[i[0]] == '\\' && ++i[0])
		output[i[1]++] = str[i[0]++];
	else
		output[i[1]++] = str[i[0]++];
}

char	*rem_quotes(const char *str)
{
	size_t			i[2];
	char			*output;
	t_quote_mode	mode;

	output = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_bzero(i, sizeof(size_t) * 2);
	mode = QUOTE_NONE;
	while (i[0] < ft_strlen(str))
	{
		if (mode == QUOTE_NONE)
			handle_nonquoted(str, i, output, &mode);
		else if (mode == QUOTE_DOUBLE && str[i[0]] == '"' && ++i[0])
			mode = QUOTE_NONE;
		else if (mode == QUOTE_SINGLE && str[i[0]] == '\'' && ++i[0])
			mode = QUOTE_NONE;
		else if (str[i[0]] == '\\')
			quoted_backslash(str, i, output, mode);
		else
			output[i[1]++] = str[i[0]++];
	}
	return (output);
}

void rem_quotes_in_place(char *str)
{
	size_t			i[2];
	char			*output;
	t_quote_mode	mode;

	output = str;
	ft_bzero(i, sizeof(size_t) * 2);
	mode = QUOTE_NONE;
	while (i[0] < ft_strlen(str))
	{
		if (mode == QUOTE_NONE)
			handle_nonquoted(str, i, output, &mode);
		else if (mode == QUOTE_DOUBLE && str[i[0]] == '"' && ++i[0])
			mode = QUOTE_NONE;
		else if (mode == QUOTE_SINGLE && str[i[0]] == '\'' && ++i[0])
			mode = QUOTE_NONE;
		else if (str[i[0]] == '\\')
			quoted_backslash(str, i, output, mode);
		else
			output[i[1]++] = str[i[0]++];
	}
	output[i[1]] = '\0';
}
