/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:40:45 by hurb              #+#    #+#             */
/*   Updated: 2025/05/07 10:39:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_arrclear(void **chunks, void (*f)(void *))
{
	void	**ch;

	if (!chunks || !*chunks)
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
