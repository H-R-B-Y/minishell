/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:16:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 17:43:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#define TC str[i[0]]

void	_write_char(char *too, char what, size_t *idx)
{
	*too = what;
	idx[0]++;
	idx[1]++;
}

char	*remove_quotes(char *str)
{
	size_t			i[2];
	t_quote_mode	mode;
	char			*output;

	output = ft_calloc(ft_strlen(str), sizeof(char));
	ft_bzero(i, sizeof(size_t) * 2);
	mode = QUOTE_NONE;
	while (str[i[0]])
	{
		if (mode == QUOTE_NONE)
		{
			if (TC == '\'')
			{
				mode = QUOTE_SINGLE;
				i[0]++;
				continue ;
			}
			if (TC == '"')
			{
				mode = QUOTE_DOUBLE;
				i[0]++;
				continue ;
			}
			if (TC == '\\')
				i[0]++;
			_write_char(&output[i[1]], TC, i);
			continue ;
		}
		if (TC == '\'' && mode == QUOTE_SINGLE)
		{
			mode = QUOTE_NONE;
			i[0]++;
			continue;
		}
		if (TC == '"' && mode == QUOTE_DOUBLE)
		{
			mode = QUOTE_NONE;
			i[0]++;
			continue;
		}
		if (TC == '\\' && mode == QUOTE_DOUBLE)
			i[0]++;
		_write_char(&output[i[1]], TC, i);
		continue;
	}
	return (output);
}
