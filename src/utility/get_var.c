/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:52:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/01 14:30:41 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef struct	s_expansion
{
	char	**out;
	const char	*value;
	size_t		v_i;
	size_t		o_i;
	t_quote_mode	mode;
	int			flag;
} t_expansion;

// TODO: null check this please harvey!
void	*vecjoin(void **vec1, void **vec2)
{
	size_t	size;
	void	**out;

	size = ft_arrlen(vec1) + ft_arrlen(vec2);
	out = ft_calloc(size + 1, sizeof(void *));
	ft_memmove(out, vec1, ft_arrlen(vec1) * sizeof(void *));
	ft_memmove(out + ft_arrlen(vec1), vec2, ft_arrlen(vec2) * sizeof(void *));
	return (out);
}

// static void	special_var_base(char **output, char *append)
// {
// 	ft_dirtyswap((void *)output, ft_strjoin(*output, append), free);
// }
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
		(struct s_special_var){.match="0123456789",.f=special_argv}, // special case for $"" and $''
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
	t_expansion *ex,
	char **res
)
{
	const struct s_special_var	*_case;
	ssize_t						ret;

	_case = get_special(ex->value[ex->v_i]);
	if (!_case)
		return (-1);
	ret = _case->f(shell, &ex->value[ex->v_i], res);
	ex->v_i += ret;
	return (ret);
}

ssize_t	is_other(t_minishell *shell, t_expansion *ex, char **res)
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

ssize_t	handle_var(t_minishell *shell, t_expansion *ex)
{
	ssize_t	_case;
	char	*res;
	char	**split;
	char	**new_out;

	_case = is_special(shell, ex, &res);
	if (_case == 0)
		return (perror_exit(shell, "minishell:parameter"), -1);
	else if (_case < 0) // we only need to split the result when we are using non special? 
	{
		// since this returns the result of the expanded variable
		// we should probably do the same in the case of is special,
		// and only increment the strpointr to the character after the special character
		_case = is_other(shell, ex, &res); 
		if (_case < 0) // Is other should return the resulting variable
			perror_exit(shell, "minishell:parameter");
	}
	if (ex->flag & 2 && ex->mode == QUOTE_NONE)
	{
		// check if it should be split, or just split it
		split = ft_splitfn(res, ft_iswhitespace); // expand this case to be IFS
		if (ft_strchr(" \t", res[0]) || !ex->out[0][0]) // this either joins the next word with the last word or assigns the next word to the next slot in the out array
		{
			ft_dirtyswap((void *)&ex->out[ex->o_i], ft_strjoin(ex->out[ex->o_i], split[0]), free);
			new_out = (void *)vecjoin((void *)ex->out, (void *)&split[1]);
		}
		else
			new_out = vecjoin((void *)ex->out, (void *)split);
		ft_dirtyswap((void *)&ex->out, new_out, free); // this is ok because we dont want to free the items just the array
		new_out = (void *)ft_arradd_back((void *)ex->out, ft_strdup(""));
		ft_dirtyswap((void *)&ex->out, new_out, free); // this is ok because we dont want to free the items just the array
		ex->o_i += ft_arrlen((void *)split);
	}
	else
		ft_dirtyswap((void *)&ex->out[ex->o_i], ft_strjoin(ex->out[ex->o_i], res), free);
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

 // assumes value containes all dollar signs
// char	**expand_and_split(t_minishell *shell, const char *value, int flag)
// {
// 	char			**out;
// 	char			*tmp;
// 	ssize_t			i[3]; // 0 index in value, 1 index moved, 2 index of string currently being worked on
// 	t_quote_mode	q_mode;

// 	i[0] = 0;
// 	i[2] = 0;
// 	q_mode = QUOTE_NONE;
// 	out = ft_calloc(2, sizeof(char *));
// 	out[0] = ft_strdup("");
// 	while (value[i[0]])
// 	{
// 		i[1] = 0;
// 		if (value[i[0]] && value[i[0]] == '$'
// 			&& (q_mode == QUOTE_NONE || q_mode == QUOTE_DOUBLE) && ++i[0])
// 			i[0] += handle_var(shell, &value[i[0]], &out); // increment how many places we have moved in the string
// 		else if (value[i[0]] && flag)
// 			i[1] += handle_char(&value[i[0]], &q_mode); // increment until the next var (checking for quote modes)
// 		else if (value[i[0]])
// 			i[1] += 1;
// 		if (!i[1])
// 			continue;
// 		tmp = ft_substr(value, i[0], i[1]);
// 		(ft_dirtyswap((void *)&out, ft_strjoin(out, tmp), free), free(tmp));
// 		i[0] += i[1];
// 	}
// 	return (out);
// }

/*


https://pubs.opengroup.org/onlinepubs/9799919799/

volume: shell and utilities

2.6.5 Field Splitting

details the process of how fields should be split in a way as to not
alter any values that did not originate from the result of an expansion

This is important but also very difficult to track, so i integrated
the formula into the expansion function.

//

Things that still need to be tested:

empty expansion as a result of IFS removal, 

function for splitting that uses IFS

IFS variable needs to be added to shell internals

empty expansions

expansions that contain more than one word

expansions that are followed by one or more non alnum char

expansions that contain different levels or quoted/unquoted strings

quotes that are created as a result of expansion should probably be escaped
so that the resulting quotes are not removed as a result of quote removal

Note: expansion of a redirect filename that then becomes multiple words causes an error in bash, this should be handled

expansion needs to happen on filenames that are associated with redirects but not on the heredoc deliminator

the resulting bytes of a split can be left joined with the previous parts of the token if and only if there are no
IFS characters at the start of the result.

*/

char	**expand_and_split(t_minishell *shell, const char *value, int flag)
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
			handle_var(shell, &ex); // increment will be done in lower scope // this can return an error case;
		else if (ex.value[ex.v_i] && flag)
			delta_v += handle_char(&ex.value[ex.v_i], &ex.mode); // increment until the next var (checking for quote modes)
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