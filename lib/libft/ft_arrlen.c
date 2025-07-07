/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:29:32 by hurb              #+#    #+#             */
/*   Updated: 2025/06/27 17:40:53 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_arrlen(void **chunks)
{
	size_t	i;

	if (!chunks)
		return (0);
	i = 0;
	while (chunks[i])
	{
		if (!chunks[i])
			break ;
		i++;
	}
	return (i);
}
