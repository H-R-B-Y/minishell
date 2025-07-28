/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:52:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 16:40:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	_expand_write_var(t_minishell *shell, char **output, char *str, size_t *i)
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
*/
static int	_is_num(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

static int	get_special(t_minishell *shell, const char *name, char **output)
{
	if (name[0] == '?' && !name[1])
		*output = ft_itoa(shell->return_code);
	else if (name[0] == '$' && !name[1])
		*output = ft_itoa(shell->my_pid);
	else if (name[0] == '_' && !name[1]) // TODO: figure out how to handle this?
		*output = ft_strdup("NOT IMPLEMENTED YET\n");
	else if (_is_num(name))
	{
		if (ft_atoi(name) < shell->argc)
			*output = ft_strdup(shell->argv[ft_atoi(name)]);
		else
			*output = ft_strdup("");
	}
	else
		return (0);
	return (1);
}

char	*get_var(t_minishell *shell, const char *name)
{
	char	*output;

	if (!name)
		return (ft_strdup("$"));
	if (get_special(shell, name, &output))
		return (output);
	else
		return (ft_strdup(s_get_envany(shell, name)));
}
