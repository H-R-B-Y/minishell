/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:40:45 by hurb              #+#    #+#             */
/*   Updated: 2025/06/26 15:05:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_arrclear(void **chunks, void (*f)(void *))
{
	void	**ch;

	if (!chunks)
		return ;
	ch = chunks;
	while (*chunks)
	{
		if (f)
			f(*chunks);
		*chunks = 0;
		chunks++;
	}
	free(ch);
}
