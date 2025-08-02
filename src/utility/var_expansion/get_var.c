/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:52:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 13:08:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "./var_expansion.h"

static ssize_t	is_special(t_minishell *shell,
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

static ssize_t	is_normal(t_minishell *shell,
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
	*res = s_get_envany(shell, str);
	free(str);
	ex->v_i += i;
	return (i);
}

static ssize_t	_handle_word_split(t_expansion *ex,
	char **res
)
{
	char	**split;
	char	**new_out;
	size_t	len;

	split = ft_splitfn(*res, ft_iswhitespace);
	len = ft_arrlen((void *)split);
	if (!split)
		return (-1);
	if (!ft_iswhitespace((*res)[0]) || !ex->out[ex->o_i][0])
	{
		ft_dirtyswap((void *)&ex->out[ex->o_i],
			ft_strjoin(ex->out[ex->o_i], split[0]), free);
		new_out = arrjoin((void *)ex->out, (void *)&split[1]);
	}
	else
		new_out = arrjoin((void *)ex->out, (void *)split);
	ft_dirtyswap((void *)&ex->out, new_out, free);
	if (ft_iswhitespace((*res)[ft_strlen(*res) - 1]))
	{
		new_out = (void *)ft_arradd_back((void *)ex->out, ft_strdup(""));
		ft_dirtyswap((void *)&ex->out, new_out, free);
		ex->o_i += len;
	}
	else
		ex->o_i += (len - 1);
	return (free(split), len);
}

ssize_t	handle_var(t_minishell *shell,
	t_expansion *ex
)
{
	ssize_t	_case;
	char	*res;

	_case = is_special(shell, ex, &res);
	if (_case < 0)
		return (perror_exit(shell, "minishell:parameter"), -1);
	else if (_case == 0)
	{
		_case = is_normal(shell, ex, &res); 
		if (_case < 0)
			perror_exit(shell, "minishell:parameter");
	}
	if (res && ex->flag & 2 && ex->mode == QUOTE_NONE)
	{
		_case = _handle_word_split(ex, &res);
		if (_case < 0)
			perror_exit(shell, "minishell:parameter");
	}
	else
		ft_dirtyswap((void *)&ex->out[ex->o_i],
			ft_strjoin(ex->out[ex->o_i], (char *[2]){res, ""}[!res]), free);
	return (_case);
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
			*mode = QUOTE_DOUBLE;
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

char	**expand_and_split(t_minishell *shell,
	const char *value,
	int flag
)
{
	t_expansion	ex;
	ssize_t		delta_v;

	ex = (t_expansion){.mode = QUOTE_NONE,
		.out = ft_calloc(2, sizeof(char *)), .o_i = 0,
		.value = value, .v_i = 0, .flag = flag};
	ex.out[ex.o_i] = ft_strdup("");
	while (ex.value[ex.v_i])
	{
		delta_v = 0;
		if (ex.value[ex.v_i] && ex.value[ex.v_i] == '$'
			&& (ex.mode == QUOTE_NONE || ex.mode == QUOTE_DOUBLE) && ++ex.v_i)
			handle_var(shell, &ex);
		else if (ex.value[ex.v_i] && flag)
			delta_v += handle_char(&ex.value[ex.v_i], &ex.mode);
		else if (ex.value[ex.v_i])
			delta_v += 1;
		if (!delta_v)
			continue;
		(ft_dirtyswap((void *)&ex.out[ex.o_i], ft_strjoin(ex.out[ex.o_i], ft_substr(ex.value, ex.v_i, delta_v)), free));
		ex.v_i += delta_v;
	}
	if (!*ex.out[ex.o_i])
		ft_dirtyswap((void *)&ex.out, (void *)ft_arrdel_atindex((void *)ex.out, ex.o_i, free), free);
	return (ex.out);
}
