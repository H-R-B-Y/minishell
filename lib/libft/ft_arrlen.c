/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:29:32 by hurb              #+#    #+#             */
/*   Updated: 2025/08/02 18:56:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_arrlen(void **chunks)
{
	size_t	i;

	if (!chunks)
		return (0);
	i = 0;
	while (chunks[i])
	{
		if (!chunks[i])
			break ;
		i++;
	}
	return (i);
}
