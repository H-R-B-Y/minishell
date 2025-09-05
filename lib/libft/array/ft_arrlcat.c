/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:37:45 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/26 10:54:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arr.h"
#include <stdlib.h>

size_t	ft_arrlcat(void **dest, void **src, size_t size)
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
			return (ft_arrclear(dest, free), 0);
		idx++;
	}
	dest[idx + dl] = (void *)0;
	return (dl + sl);
}
