/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arriter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:45:09 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:50:24 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_arriter(void **arr, void *(*f)(void *))
{
	size_t	idx;

	if (!arr)
		return ;
	idx = 0;
	while (arr[idx])
		f(arr[idx++]);
}
