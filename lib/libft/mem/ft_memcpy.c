/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:18:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:42:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	size_t			i;

	if (!dest && !src)
		return (0);
	if (!dest)
		return (0);
	i = 0;
	d = dest;
	while (i < n)
	{
		d[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
