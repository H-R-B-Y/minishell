/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:28:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:04:58 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(const char *s, const int c)
{
	char	*start;

	if (!s)
		return (0);
	start = (char *)s;
	while (*s)
		s++;
	while (start < s && (unsigned char)*s != (unsigned char)c)
		s--;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
