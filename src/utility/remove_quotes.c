/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:16:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/16 12:42:32 by hbreeze          ###   ########.fr       */
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

int _expand_write_var(t_minishell *shell, char **output, char *str, size_t *i)
{
	char	*old;
	size_t	vlen;
	// size_t	xpded_len;
	char	*xpded_value;
	char	*v_name;

	old = *output;
	if (!ft_isalnum((str)[i[0] + 1]))
		return (_write_char(&(*output)[i[1]], TC, i), 1);
	i[0]++;
	if (ft_isdigit((str)[i[0]]))
		return (i[0]++, 1);
	
	printf("\nhere 1 old : %s\n", old);
		
	vlen = 0;
	while (ft_isalnum((str)[i[0] + vlen]))
		vlen++;
	v_name = ft_strndup(str + i[0], vlen);
	if (!v_name)
		return (perror("minishell: var expansion"), 0);
	i[0] += vlen;
	printf("\nhere 1 old : %s ; v_name : %s ; v_len : %ld\n", old, v_name, vlen);
	xpded_value = s_get_envany(shell, v_name);
	if (!ft_strcmp(xpded_value, ""))
		return (free(v_name), 1);
	printf("\nhere 1 old : %s ; xpded_value : %s\n", old, xpded_value);
	*output = ft_calloc(ft_strlen(str + i[0]) + ft_strlen(old) + ft_strlen(xpded_value) + 1, sizeof(char));
	if (!(*output))
		return (*output = old, free(v_name), perror("minishell: var expansion"), 0);
	ft_memcpy(*output, old, ft_strlen(old));
	ft_strlcat(*output, xpded_value, ft_strlen(str + i[0]) + ft_strlen(old) + ft_strlen(xpded_value) + 1);
	i[1] += ft_strlen(xpded_value);
	return (free(v_name), free(old), 0);
}

char	*remove_quotes(char *str, t_minishell *shell)
{
	size_t			i[2];
	t_quote_mode	mode;
	char			*output;

	output = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_bzero(i, sizeof(size_t) * 2);
	mode = QUOTE_NONE;
	while (str[i[0]])
	{
		if (mode == QUOTE_NONE)
		{
			if (str[i[0]] == '\'')
			{
				mode = QUOTE_SINGLE;
				i[0]++;
				continue ;
			}
			if (str[i[0]] == '"')
			{
				mode = QUOTE_DOUBLE;
				i[0]++;
				continue ;
			}
			if (str[i[0]] == '\\')
			{
				if (ft_strchr("$'\"\\", str[i[0]]))
				{
					str[i[0]]++;
					_write_char(&output[i[1]], str[i[0]], i);
					continue ;
				}
				else
					_write_char(&output[i[1]], str[i[0]], i);
			}
			if (str[i[0]] == '$' && (mode == QUOTE_DOUBLE || mode == QUOTE_NONE))
			{
				_expand_write_var(shell, &output, str, i);
				continue ;
			}
			_write_char(&output[i[1]], str[i[0]], i);
			continue ;
		}
		if (str[i[0]] == '\'' && mode == QUOTE_SINGLE)
		{
			mode = QUOTE_NONE;
			i[0]++;
			continue;
		}
		if (str[i[0]] == '"' && mode == QUOTE_DOUBLE)
		{
			mode = QUOTE_NONE;
			i[0]++;
			continue;
		}
		if (str[i[0]] == '$' && (mode == QUOTE_DOUBLE || mode == QUOTE_NONE))
		{
			_expand_write_var(shell, &output, str, i);
			continue;
		}
		if (str[i[0]] == '\\' && mode == QUOTE_DOUBLE)
		{
			if (ft_strchr("$'\"\\", str[i[0]]))
			{
				str[i[0]]++;
				_write_char(&output[i[1]], str[i[0]], i);
				continue ;
			}
			else
				_write_char(&output[i[1]], str[i[0]], i);
		}
		_write_char(&output[i[1]], str[i[0]], i);
		continue;
	}
	return (output);
}
