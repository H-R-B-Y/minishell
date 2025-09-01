/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvecjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:00:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 12:04:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strvecjoin(const char **arr)
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