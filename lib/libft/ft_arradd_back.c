/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:52:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/26 15:05:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	**ft_arradd_back(void **arr, void *newitem)
{
	void	**output;
	size_t	len;

	if (!arr)
		return (0);
	len = ft_arrlen(arr);
	output = ft_calloc(len + 2, sizeof(void *));
	ft_memmove(output, arr, len * sizeof(void *));
	output[len] = newitem;
	return (output);
}
