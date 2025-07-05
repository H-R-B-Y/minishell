/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arriter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:45:09 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/26 14:28:32 by hbreeze          ###   ########.fr       */
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