/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirtyswap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:10:32 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:42:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_dirtyswap(void **a, void *b, void (*del)(void *))
{
	if (!a)
		return ((void *)0);
	if (del)
		del(*a);
	*a = b;
	return (b);
}
