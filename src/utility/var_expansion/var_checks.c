/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:54:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 23:47:24 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "./var_expansion.h"

size_t	ft_strcntchrset(const char *str, const char *set)
{
	size_t	count;
	size_t	i;

	if (!str || !set || !*set)
		return (0);
	count = 0;	
	i = 0;
	while (str[i])
		count += ft_strcountchar(set, str[i++]);
	return (count);
}

char	*mark_quotes(const char *expanded)
{
	size_t	qcnt;
	char	*newstr;
	size_t	i[2];
	
	if (!expanded)
		return (NULL);
	ft_bzero(i, sizeof(size_t) * 2);
	newstr = NULL;
	qcnt = ft_strcntchrset(expanded, "\\\"\'");
	if (qcnt)
	{
		newstr = ft_calloc(ft_strlen(expanded) + qcnt + 1, sizeof(char));
		if (!newstr)
			return (NULL);
		while (expanded[i[0]])
		{
			if (ft_strcountchar("\\\"\'", expanded[i[0]]))
				newstr[i[1]++] = '\\';
			newstr[i[1]++] = expanded[i[0]++];
		}
	}
	else
		newstr = ft_strdup(expanded);
	return (newstr);
}

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
	if(!ft_dirtyswap((void *)res, mark_quotes(*res), free))
		perror_exit(shell, "parameter");
	if (!ft_strchr("\'\"", ex->value[ex->v_i]))
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
	if(!ft_dirtyswap((void *)res, mark_quotes(*res), free))
		perror_exit(shell, "parameter");
	ex->v_i += i;
	return (i);
}
