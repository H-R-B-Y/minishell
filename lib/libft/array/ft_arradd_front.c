/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:46:03 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/05 21:47:59 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

void	**ft_arradd_front(void **arr, void *newitem)
{
	void	**output;
	size_t	len;

	if (!arr)
		len = 0;
	else
		len = ft_arrlen(arr);
	output = ft_calloc(len + 2, sizeof(void *));
	if (!output)
		return (0);
	output[0] = newitem;
	ft_memmove(&output[1], arr, len * sizeof(void *));
	return (output);
}
