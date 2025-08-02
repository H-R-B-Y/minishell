/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:54:04 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 21:09:03 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_words(const char	*str)
{
	return (ft_strcountchar(str, '\n') + 1);
}

static void	*_empty_str_case(void ***output)
{
	return (ft_dirtyswap((void *)output,
			ft_arradd_front((void *)*output,
				ft_strdup("\n")), free)
	);
}

char	**simple_split(const char *str, t_readline_data *data)
{
	size_t	idx[3];
	char	*next;
	char	**output;

	output = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!output)
		return (0);
	ft_memset(idx, 0, sizeof(idx));
	if (!str[idx[1]] && data->last_line)
		return (_empty_str_case((void *)&output));
	while (str[idx[1]])
	{
		idx[0] = idx[1];
		next = ft_strchr(str + idx[0], '\n');
		if (!next)
			while (str[idx[1]])
				idx[1]++;
		else
			idx[1] = (next - str) + 1;
		output[idx[2]++] = ft_substr(str, idx[0], idx[1] - idx[0]);
	}
	return (output);
}
