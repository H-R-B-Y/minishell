/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:38:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/22 13:59:24 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char		*s1_i;
	const char		*s2_i;
	size_t			index;

	s1_i = s1;
	s2_i = s2;
	index = 0;
	if (!n || !s1 || !s2)
		return (0);
	while (index + 1 < n
		&& *s1_i
		&& *s2_i
		&& (*s1_i == *s2_i)
	)
	{
		s1_i++;
		s2_i++;
		index++;
	}
	return ((unsigned char)*s1_i - (unsigned char)*s2_i);
}
