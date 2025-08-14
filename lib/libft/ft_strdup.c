/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:08:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:49:41 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./include/libft.h"

char	*ft_strdup(const char *src)
{
	size_t		len;
	size_t		i;
	char		*output;

	if (!src)
		return (0);
	len = ft_strlen(src);
	output = malloc((unsigned long)len + 1);
	if (output == 0)
		return (0);
	i = 0;
	output[len] = '\0';
	while (src[i])
	{
		output[i] = src[i];
		i++;
	}
	return (output);
}
