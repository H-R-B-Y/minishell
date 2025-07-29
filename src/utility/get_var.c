/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:52:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 15:14:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	special_var_base(char **output, char *append)
{
	ft_dirtyswap((void *)output, ft_strjoin(*output, append), free);
}
static ssize_t	special_last_param(t_minishell *shell,
	const char *value,
	char **output
)
{
	char	*str;

	(void)value;(void)shell;
	str = ft_strdup("NOT IMPLEMENTED");
	special_var_base(output, str);
	free(str);
	return (1);
}

static ssize_t	special_pid(t_minishell *shell,
	const char *value,
	char **output
)
{
	char	*str;

	(void)value;(void)shell;
	str = ft_itoa(shell->my_pid);
	special_var_base(output, str);
	free(str);
	return (1);
}

static ssize_t	special_result(t_minishell *shell,
	const char *value,
	char **output
)
{
	char	*str;

	(void)value;(void)shell;
	str = ft_itoa(shell->return_code);
	special_var_base(output, str);
	free(str);
	return (1);
}

static ssize_t	special_argv(t_minishell *shell,
	const char *value,
	char **output
)
{
	char	*str;
	int		i;

	i = *value - '0';
	if (i < shell->argc)
		str = ft_strdup(shell->argv[i]);
	else
		str = ft_strdup(" ");
	special_var_base(output, str);
	free(str);
	return (1);
}

struct s_special_var
{
	const char	*match;
	ssize_t		(*f)(t_minishell *, const char *, char **); // typedef this
};

static const struct s_special_var	*get_special(char c)
{
	int									i;
	static const struct	s_special_var	cases[5] = {
		(struct s_special_var){.match="_",.f=special_last_param},
		(struct s_special_var){.match="?",.f=special_result},
		(struct s_special_var){.match="$",.f=special_pid},
		(struct s_special_var){.match="0123456789",.f=special_argv},
		(struct s_special_var){.match=0,.f=0}
	};

	i = 0;
	if (!c)
		return (0);
	while (cases[i].match)
	{
		if (ft_strchr(cases[i].match, c))
			return (&cases[i]);
		i++;
	}
	return (0);
}

static ssize_t	is_special(t_minishell *shell,
	const char *value,
	char **output
)
{
	const struct s_special_var	*_case;
	ssize_t						ret;
	char						*base;
	size_t						i;

	_case = get_special(*value);
	if (!_case)
	{
		if (!ft_isalnum(*value))
			return (special_var_base(output, "$"), 0);
		return (-1);
	}
	ret = _case->f(shell, value, output);
	i = 0;
	if (ret > 0)
	{
		while(value[ret + i] && ft_isalnum(value[ret + i]))
			i++;
		base = ft_substr(value, ret, i);
		(special_var_base(output, base), free(base));
	}
	return (ret + i);
}

size_t	is_other(t_minishell *shell, const char *value, char **output)
{
	size_t	i;
	char	*str;
	char	*val;

	i = 0;
	while (value[i] && ft_isalnum(value[i]))
		i++;
	str = ft_substr(value, 0, i);
	val = s_get_envany(shell, str);
	free(str);
	ft_dirtyswap((void *)output, ft_strjoin(*output, val), free);
	return (i);
}

ssize_t	handle_var(t_minishell *shell, const char *value, char **output)
{
	ssize_t	_case;

	// if (!ft_isalnum(*value))
	// 	return (ft_dirtyswap((void *)output, ft_strjoin(*output, "$"), free), 0);
	_case = is_special(shell, value, output);
	if (_case >= 0)
		return (_case);
	else if (_case < 0)
		return is_other(shell, value, output);
	return (perror_exit(shell, "minishell:arg expansion"), -1);
}

ssize_t	handle_char(const char *value,
	t_quote_mode *mode
)
{
	ssize_t	i;

	i = 1;
	if (*mode == QUOTE_NONE)
	{
		if (*value == '\'')
			*mode = QUOTE_SINGLE;
		else if (*value == '"')
			*mode = QUOTE_SINGLE;
		else if (*value == '\\')
			i += 1;
	}
	else if ((*mode == QUOTE_SINGLE && *value == '\'')
		|| (*mode == QUOTE_DOUBLE && *value == '"'))
		*mode = QUOTE_NONE;
	else if (*mode == QUOTE_DOUBLE && *value == '\\')
		i += 1;
	return (i);
}

 // assumes value containes all dollar signs
char	*get_var(t_minishell *shell, const char *value, int flag)
{
	char			*out;
	ssize_t			i[2];
	t_quote_mode	p;
	char			*tmp;

	i[0] = 0;
	p = QUOTE_NONE;
	out = ft_strdup("");
	while (value[i[0]])
	{
		i[1] = 0;
		if (value[i[0]] && value[i[0]] == '$' && ++i[0]
			&& (p == QUOTE_NONE || p == QUOTE_DOUBLE))
			i[0] += handle_var(shell, &value[i[0]], &out);
		else if (value[i[0]] && flag)
			i[1] += handle_char(&value[i[0]], &p);
		else if (value[i[0]])
			i[1] += 1;
		if (!i[1])
			continue;
		tmp = ft_substr(value, i[0], i[1]);
		(ft_dirtyswap((void *)&out, ft_strjoin(out, tmp), free), free(tmp));
		i[0] += i[1];
	}
	return (out);
}
