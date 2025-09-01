/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:52:44 by hurb              #+#    #+#             */
/*   Updated: 2025/08/26 10:53:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"

void	**ft_arrmap(void **arr, void *(*f)(void *), void (*del)(void *))
{
	size_t	len;
	size_t	idx;
	void	**output;

	if (!arr)
		return ((void *)0);
	len = ft_arrlen(arr);
	output = ft_calloc(len + 1, sizeof(void *));
	idx = 0;
	while (arr[idx])
	{
		output[idx] = f(arr[idx]);
		if (!output[idx])
		{
			ft_arrclear(output, del);
			return ((void *)0);
		}
		idx++;
	}
	return (output);
}
