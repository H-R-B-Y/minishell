/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:49:53 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 00:49:55 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_arrfree(void **chunks)
{
	void	**ch;

	if (!chunks)
		return ;
	ch = chunks;
	while (*chunks)
	{
		free(*chunks);
		*chunks = 0;
		chunks++;
	}
	free(ch);
}
