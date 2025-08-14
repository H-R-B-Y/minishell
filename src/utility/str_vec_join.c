/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_vec_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:18:06 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 15:41:49 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_vec_join(const char **arr)
{
	size_t	size;
	size_t	index;
	size_t	write_head;
	char	*out;

	size = 0;
	index = 0;
	while (arr[index])
		size += ft_strlen(arr[index++]);
	index = 0;
	write_head = 0;
	out = ft_calloc(size + 1, sizeof(char));
	if (!out)
		return ((void *)0);
	while (arr[index])
	{
		ft_memmove(out + write_head, arr[index],
			sizeof(char) * ft_strlen(arr[index]));
		write_head += ft_strlen(arr[index]);
		index++;
	}
	return (out);
}
