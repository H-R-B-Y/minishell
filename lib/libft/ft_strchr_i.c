/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:38:19 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:38:35 by cquinter         ###   ########.fr       */
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
