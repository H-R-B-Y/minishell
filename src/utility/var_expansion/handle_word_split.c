/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:57:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/04 14:03:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "./var_expansion.h"

void	_expensive_free_that_i_wish_i_didnt_have_to_do(char ***split, char **arr)
{
	size_t	i;
	size_t	i2;
	int		flag;
	i = 0;
	while ((*split)[i])
	{
		flag = 0;
		i2 = 0;
		while (arr[i2])
		{
			if ((*split)[i] == arr[i2])
				flag = 1;
			i2++;
		}
		if (!flag)
			free((*split)[i]);
		i++;
	}
	free((*split));
}

size_t	_pre_space(t_expansion *ex, char **res, char **split, char ***new_out)
{
	if (!ft_iswhitespace((*res)[0]) || !ex->out[ex->o_i][0])
	{
		ft_dirtyswap((void *)&ex->out[ex->o_i],
			ft_strjoin(ex->out[ex->o_i], split[0]), free);
		*new_out = arrjoin((void *)ex->out, (void *)&split[1]);
		return (-1);
	}
	*new_out = arrjoin((void *)ex->out, (void *)split);
	return (0);
}

size_t	_post_space(t_expansion *ex, char **res, char **split, char ***new_out)
{
	(void)split;
	if (ft_iswhitespace((*res)[ft_strlen(*res) - 1]))
	{
		new_out = (void *)ft_arradd_back((void *)ex->out, ft_strdup(""));
		ft_dirtyswap((void *)&ex->out, new_out, free);
		return (1);
	}
	return (0);
}

ssize_t	_handle_word_split(t_expansion *ex,
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
	len += _pre_space(ex, res, split, &new_out);
	ft_dirtyswap((void *)&ex->out, new_out, free);
	len += _post_space(ex, res, split, &new_out);
	ex->o_i += len;
	_expensive_free_that_i_wish_i_didnt_have_to_do(&split, ex->out);
	return (len);
}
