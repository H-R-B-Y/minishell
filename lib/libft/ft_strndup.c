/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 00:48:49 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		i;
	char		*output;

	if (!src)
		return (0);
	output = malloc(sizeof(char) * n + 1);
	if (!output)
		return (NULL);
	i = 0;
	output[n] = '\0';
	while (src[i] && i < n)
	{
		output[i] = src[i];
		i++;
	}
	return (output);
}
