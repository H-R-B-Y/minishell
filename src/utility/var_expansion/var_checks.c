/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:54:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/04 12:56:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "./var_expansion.h"

ssize_t	is_special(t_minishell *shell,
	t_expansion *ex,
	char **res
)
{
	const struct s_special_var	*_case;
	ssize_t						ret;

	_case = get_special(ex->value[ex->v_i]);
	if (!_case)
		return (0);
	ret = _case->f(shell, &ex->value[ex->v_i], res);
	ex->v_i += ret;
	return (ret);
}

ssize_t	is_normal(t_minishell *shell,
	t_expansion *ex,
	char **res
)
{
	ssize_t	i;
	char	*str;

	i = 0;
	while (ex->value[ex->v_i + i]
		&& ft_isalnum(ex->value[ex->v_i + i]))
		i++;
	str = ft_substr(&ex->value[ex->v_i], 0, i);
	if (*str)
		*res = ft_strdup(s_get_envany(shell, str));
	else
		*res = ft_strdup("$");
	free(str);
	ex->v_i += i;
	return (i);
}
