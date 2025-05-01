/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurb <hurb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:52:44 by hurb              #+#    #+#             */
/*   Updated: 2025/02/22 17:16:18 by hurb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include "include/get_next_line.h"

void	**ft_arrmap(void **arr, void *(*f)(void *), void (*del)(void *))
{
	size_t	len;
	size_t	idx;
	void	**output;

	len = ft_arrlen(arr);
	output = malloc(sizeof(void *) * (len + 1));
	zeroit(output, sizeof(void *) * (len + 1));
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
