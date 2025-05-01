/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurb <hurb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:40:45 by hurb              #+#    #+#             */
/*   Updated: 2025/02/22 18:36:02 by hurb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_arrclear(void **chunks, void (*f)(void *))
{
	void	**ch;

	if (!chunks || !*chunks || !f)
		return ;
	ch = chunks;
	while (*chunks)
	{
		f(*chunks);
		*chunks = 0;
		chunks++;
	}
	free(ch);
}
