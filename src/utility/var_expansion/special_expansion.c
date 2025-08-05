/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:05:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 13:37:31 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./var_expansion.h"
#include "../../../include/minishell.h"


static ssize_t	special_translation(t_minishell *shell,
	const char *value,
	char **output
)
{
	(void)value;(void)shell;
	*output = ft_strdup(" ");
	ft_printf("Note: $\"\": locale translation not implemented\n");
	return (1);
}

static ssize_t	special_last_param(t_minishell *shell,
	const char *value,
	char **output
)
{
	char	*to_xpnd;
	
	(void)value;(void)shell;
	to_xpnd = s_get_envany(shell, "_");
	if (!to_xpnd)
		*output = ft_strdup("_");
	else
		*output = ft_strdup(to_xpnd);
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
	static const struct	s_special_var	cases[6] = {
		(struct s_special_var){.match="\"",.f=special_translation},
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
