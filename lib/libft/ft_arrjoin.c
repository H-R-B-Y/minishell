/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:06:20 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 18:56:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	**ft_arrjoin(void **arr1, void **arr2)
{
	void	**output;
	size_t	lengths[2];

	if (!arr1 && !arr2)
		return (0);
	lengths[0] = ft_arrlen(arr1);
	lengths[1] = ft_arrlen(arr2);
	output = calloc(lengths[0] + lengths[1] + 1, sizeof(void *));
	ft_memmove(output, arr1, (lengths[0]) * sizeof(void *));
	ft_memmove(output + lengths[0], arr2, (lengths[1]) * sizeof(void *));
	return (output);
}
