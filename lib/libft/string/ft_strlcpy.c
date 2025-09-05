/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:29:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:04:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	index;

	src_len = ft_strlen(src);
	if (!dest || !src || !size)
		return (src_len);
	index = 0;
	while (src[index] != '\0' && index < size)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index - 1 * !(index < size)] = 0;
	return (src_len);
}
