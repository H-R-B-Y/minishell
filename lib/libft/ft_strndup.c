/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/02 18:35:21 by cquinter         ###   ########.fr       */
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