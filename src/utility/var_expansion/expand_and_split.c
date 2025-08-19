/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:52:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/18 18:42:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "./var_expansion.h"

ssize_t	handle_var(t_minishell *shell,
	t_expansion *ex
)
{
	ssize_t	_case;
	char	*res;

	_case = is_special(shell, ex, &res);
	if (_case < 0)
		return (perror_exit(shell, "parameter"), -1);
	else if (_case == 0)
	{
		_case = is_normal(shell, ex, &res);
		if (_case < 0)
			perror_exit(shell, "parameter");
	}
	if (res && (ex->flag & 2) && ex->mode == QUOTE_NONE)
	{
		_case = _handle_word_split(ex, &res);
		if (_case < 0)
			perror_exit(shell, "parameter");
	}
	else
		ft_dirtyswap((void *)&ex->out[ex->o_i],
			ft_strjoin(ex->out[ex->o_i], (char *[2]){res, ""}[!res]), free);
	return (free(res), _case);
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

void	append_difference(t_expansion *ex, ssize_t delta)
{
	char	*temp;

	temp = ft_substr(ex->value, ex->v_i, delta);
	temp = ft_dirtyswap((void *)&temp,
			ft_strjoin(ex->out[ex->o_i], temp), free);
	ft_dirtyswap((void *)&ex->out[ex->o_i], temp, free);
}

char	**expand_and_split(t_minishell *shell,
	const char *value,
	int flag
)
{
	t_expansion	ex;
	ssize_t		delta_v;

	ex = (t_expansion){.mode = QUOTE_NONE, .out = ft_calloc(2, sizeof(char *)),
		.o_i = 0, .value = value, .v_i = 0, .flag = flag};
	ex.out[ex.o_i] = ft_strdup("");
	while (ex.v_i < ft_strlen(ex.value))
	{
		delta_v = 0;
		if (ex.value[ex.v_i] && ex.value[ex.v_i] == '$'
			&& (ex.mode == QUOTE_NONE || ex.mode == QUOTE_DOUBLE) && ++ex.v_i)
			handle_var(shell, &ex);
		else if (ex.value[ex.v_i] && (flag & 1))
			delta_v += handle_char(&ex.value[ex.v_i], &ex.mode);
		else if (ex.value[ex.v_i])
			delta_v += 1;
		if (!delta_v)
			continue ;
		append_difference(&ex, delta_v);
		ex.v_i += delta_v;
	}
	if (!*ex.out[ex.o_i] && ex.o_i > 0)
		ft_dirtyswap((void *)&ex.out,
			(void *)ft_arrdel_atindex((void *)ex.out, ex.o_i, free), free);
	return (ex.out);
}
