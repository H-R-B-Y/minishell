/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strltrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:24:48 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/25 13:27:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./include/libft.h"

char	*ft_strltrim(const char *s1, const char *set)
{
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	return (ft_strdup(s1));
}
