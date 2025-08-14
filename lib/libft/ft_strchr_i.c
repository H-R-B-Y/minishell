/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:18:42 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/13 23:51:46 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_strchr_i(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] && (unsigned char)s[i] != (unsigned char)c)
		i++;
	if ((unsigned char)s[i] == (unsigned char)c)
		return (i);
	return (-1);
}
