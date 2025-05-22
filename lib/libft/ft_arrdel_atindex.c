/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel_atindex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:20:38 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 17:57:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/libft.h"

void	**ft_arrdel_atindex(void **arr, size_t index)
{
	size_t	len;
	void	**output;

	if (!arr || !*arr)
		return (0);
	len = ft_arrlen(arr);
	output = ft_calloc(len, sizeof(void *));
	if (!output)
		return (0);
	ft_memmove(output, arr, (index) * sizeof(void *));
	ft_memmove(output + index, arr + index + 1,
		((len - 1) - index) * sizeof(void *));
	return (output);
}
