/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:40:45 by hurb              #+#    #+#             */
/*   Updated: 2025/06/29 11:43:19 by cquinter         ###   ########.fr       */
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

/*void	ft_arrclear(void ***chunks, void (*f)(void *))
{
	void	**ch;
	size_t	i;


	if (!chunks || !*chunks)
		return ;
	if (!f)
		f = free;
	i = 0;
	ch = *chunks;
	while (ch[i])
	{
		if (f)
			f(ch[i]);
		ch[i] = NULL; 
		i++;
	}
	free(ch);
	*chunks = NULL;
}*/
