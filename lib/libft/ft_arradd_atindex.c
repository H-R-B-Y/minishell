/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_atindex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:53:54 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/07 15:47:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	**ft_arradd_atindex(void **arr, void *newitem, size_t index)
{
	size_t	len;
	void	**output;

	if (!arr)
		return (0);
	if (index == 0)
		return (ft_arradd_front(arr, newitem));
	len = ft_arrlen(arr);
	if (index == len - 1)
		return (ft_arradd_back(arr, newitem));
	output = ft_calloc(len + 2, sizeof(void *));
	if (!output)
		return (0);
	ft_memmove(output, arr, index * sizeof(void *));
	output[index] = newitem;
	ft_memmove(output + index + 1, arr + index, ((len - index) + 1) * sizeof(void *));
	return (output);
}
