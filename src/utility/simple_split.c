/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:54:04 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/08 13:13:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_words(const char	*str)
{
	return (ft_strcountchar(str, '\n') + 1);
}

char	**simple_split(const char *str)
{
	size_t	count;
	size_t	idx[3];
	char	*next;
	char	**output;

	count = count_words(str);
	if (!count)
		return (0);
	output = ft_calloc(count + 1, sizeof(char *));
	idx[1] = 0;
	idx[2] = 0;
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
