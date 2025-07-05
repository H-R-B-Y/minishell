/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:46:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/26 14:28:00 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	**ft_arradd_front(void **arr, void *newitem)
{
	void	**output;
	size_t	len;

	if (!arr)
		return (0);
	len = ft_arrlen(arr);
	output = ft_calloc(len + 2, sizeof(void *));
	if (!output)
		return (0);
	output[0] = newitem;
	ft_memmove(&output[1], arr, len * sizeof(void *));
	return (output);
}
