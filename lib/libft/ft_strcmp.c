/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:27:51 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/22 14:01:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const char	*s1_i;
	const char	*s2_i;

	if (s1 == s2 || (!s1 || !s2))
		return (0);
	s1_i = s1;
	s2_i = s2;
	while (*s1_i
		&& *s2_i
		&& (*s1_i == *s2_i)
	)
	{
		s1_i++;
		s2_i++;
	}
	return ((unsigned char)*s1_i - (unsigned char)*s2_i);
}
