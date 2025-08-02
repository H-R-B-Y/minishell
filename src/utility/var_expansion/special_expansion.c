/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:05:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 17:15:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./var_expansion.h"
#include "../../../include/minishell.h"

static ssize_t	special_last_param(t_minishell *shell,
	const char *value,
	char **output
)
{
	(void)value;(void)shell;
	*output = ft_strdup("NOT IMPLEMENTED");
	return (1);
}

static ssize_t	special_pid(t_minishell *shell,
	const char *value,
	char **output
)
{
	(void)value;(void)shell;
	*output = ft_itoa(shell->my_pid);
	return (1);
}

static ssize_t	special_result(t_minishell *shell,
	const char *value,
	char **output
)
{
	(void)value;(void)shell;
	*output = ft_itoa(shell->return_code);
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
	*output = str;
	return (1);
}

const struct s_special_var	*get_special(char c)
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
