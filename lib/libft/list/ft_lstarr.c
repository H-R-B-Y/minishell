/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:24:09 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:44:02 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	**ft_lstarr(t_list *lst)
{
	size_t	size;
	size_t	i;
	void	**arr;

	if (!lst)
		return ((void *)0);
	size = ft_lstsize(lst);
	arr = ft_calloc(size + 1, sizeof(void *));
	if (!arr)
		return ((void *)0);
	i = 0;
	while (i < size)
	{
		arr[i] = ft_lstget(lst, i)->content;
		i++;
	}
	arr[size] = 0;
	return (arr);
}
