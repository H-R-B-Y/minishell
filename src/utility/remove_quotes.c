/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:16:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/09 17:57:28 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	_realloc_write(char **output, const char *to_write, const char *str, size_t *i)
{
	char	*temp;
	size_t	newlen;
	size_t	oldlen;
	size_t	to_write_len;
	
	if (!to_write)
		return (perror("minishell: ft_itoa: unable to expand $"), 1);
	temp = *output;
	to_write_len = ft_strlen(to_write);
	oldlen = i[1];
	newlen = oldlen + ft_strlen(str + i[0]) + to_write_len + 1;
	*output = ft_calloc(newlen, sizeof(char));
	if (!(*output))
		return (*output = temp, perror("minishell: var expansion"), 1);
	ft_memcpy(*output, temp, oldlen);
	ft_memcpy(*output + oldlen, to_write, to_write_len);
	if (ft_strchr("?$", str[i[0]]))
		i[0]++;
	else
		i[0] += i[2];
	i[1] += to_write_len;
	return (0);
}

char	*get_var_value(t_minishell *shell, char *str, size_t *i)
{
	size_t	vlen;
	char	*xpded_value;
	char	*v_name;

	vlen = 0;
	while (ft_isalnum((str)[i[0] + vlen]) || (str)[i[0] + vlen] == '_')
		vlen++;
	v_name = ft_strndup(str + i[0], vlen);
	if (!v_name)
		return (perror("minishell: var expansion"), NULL);
	xpded_value = ft_strdup(s_get_envany(shell, v_name));
	if (!xpded_value)
		return (free(v_name), NULL);
	i[2] = vlen;
	free(v_name);
	return (xpded_value);
}

int _expand_write_var(t_minishell *shell, char **output, char *str, size_t *i)
{
	char	*to_write;
	
	i[0]++;
	if ((str)[i[0]] == '?')
		to_write = ft_itoa(shell->return_code);
	else if ((str)[i[0]] == '$')
		to_write = ft_itoa(shell->my_pid);
	else if (str[i[0]] != '_' && !ft_isalnum((str)[i[0]])) // handle {} ??
		return ((*output)[i[1]++] = str[i[0] - 1], 1);
	else if (ft_isdigit((str)[i[0]])) // Pending: to handle argvs
		return (i[0]++, 1);
	else
		to_write = get_var_value(shell, str, i);
	if (!to_write)
		return ((*output)[i[1]++] = str[i[0] - 1], 1);
	else if (_realloc_write(output, to_write, str, i))
		return ((*output)[i[1]++] = str[i[0] - 1], free(to_write), 1);
	free(to_write);
	return (0);
}

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
	else if (str[i[0]] == '\\' && ++i[0])
		output[i[1]++] = str[i[0]++];
	else
		output[i[1]++] = str[i[0]++];
}

char	*rmv_quotes_xpnd_var(char *str, t_minishell *shell)
{
	size_t			i[3];
	t_quote_mode	mode;
	char			*output;

	output = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_bzero(i, sizeof(size_t) * 3);
	mode = QUOTE_NONE;
	while(str[i[0]])
	{
		if (str[i[0]] == '$' && (mode == QUOTE_DOUBLE || mode == QUOTE_NONE))
			_expand_write_var(shell, &output, str, i);
		else if (mode == QUOTE_NONE)
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
