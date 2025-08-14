/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:26:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 18:39:24 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./include/libft.h"

char	*ft_strrtrim(const char *s1, const char *set)
{
	size_t			size;
	char			*end;

	size = 0;
	end = (char *)s1;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	while (*end)
		end++;
	while (*(--end))
		if (*end && !ft_strchr(set, *end))
			break ;
	size = (end - s1) + 1;
	return (ft_substr(s1, 0, size));
}
