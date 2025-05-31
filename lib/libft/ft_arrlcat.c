/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:37:45 by cquinter          #+#    #+#             */
/*   Updated: 2025/05/31 16:47:50 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t ft_arrlcat(void **dest, void **src, size_t size)
{
	size_t	idx;
	size_t	dl;
	size_t	sl;
	
	if (!dest)
		return (0);
	dl = 0;
	sl = 0;
	while (dest[dl] && dl < size)
		dl++;
	while (src[sl])
		sl++;
	if (dl == size)
		return (size + sl);
	idx = 0;
	while (src[idx] && (dl + idx) < size - 1)
	{
		dest[idx + dl] = ft_strdup(src[idx]);
		if (!dest[idx])
		{
			ft_arrclear(dest, free);
			return (0);
		}
		idx++;
	}
	dest[idx + dl] = NULL;
	return (dl + sl);
}
