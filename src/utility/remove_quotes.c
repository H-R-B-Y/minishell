/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:16:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/29 13:44:16 by cquinter         ###   ########.fr       */
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

void _write_str(char **output, char *str, size_t *i)
{
	while (*str)
	{
		_write_char(&(*output)[i[1]], *str, i);
		str++;
	}
}

int _expand_write_special(t_minishell *shell, char **output, char *str, size_t *i)
{
	char	*to_write;
	// size_t	len2add;
	char	*temp;
	
	i[0]++;
	if ((str)[i[0]] == '?')
	{
		temp = *output;
		to_write = ft_itoa(shell->return_code);
		if (!to_write)
			return (perror("minishell: ft_itoa: unable to expand $"),
				_write_char(&(*output)[i[1]], str[--i[0]], i), 1);
		// len2add = ft_strlen(to_write);
		*output = ft_calloc(ft_strlen(str + i[0]) + ft_strlen(temp) + ft_strlen(to_write) + 1, sizeof(char));
		if (!(*output))
			return (*output = temp, free(to_write), perror("minishell: var expansion"), _write_char(&(*output)[i[1]], str[--i[0]], i), 1);
		ft_memcpy(*output, temp, ft_strlen(temp));
		_write_str(output, to_write, i);
		free(temp);
		free(to_write);
		return (1);
	}
	if (!ft_isalnum((str)[i[0]]))
		return (_write_char(&(*output)[i[1]], str[--i[0]], i), 1);
	if (ft_isdigit((str)[i[0]])) // Pending: to handle argvs
		return (i[0]++, 1);
	return (0);
}

int _expand_write_var(t_minishell *shell, char **output, char *str, size_t *i)
{
	char	*old;
	size_t	vlen;
	char	*xpded_value;
	char	*v_name;

	old = *output;
	if (_expand_write_special(shell, output, str, i))
		return (0);
	vlen = 0;
	while (ft_isalnum((str)[i[0] + vlen]))
		vlen++;
	v_name = ft_strndup(str + i[0], vlen);
	if (!v_name)
		return (perror("minishell: var expansion"), 0);
	i[0] += vlen;
	xpded_value = s_get_envany(shell, v_name);
	if (!ft_strcmp(xpded_value, ""))
		return (free(v_name), 1);
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
				if (ft_strchr("$'\"\\", str[i[0] + 1]))
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
