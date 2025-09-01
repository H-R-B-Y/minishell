/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:18:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:44:02 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*index;

	index = lst;
	if (!lst)
		return (0);
	while (index->next)
		index = index->next;
	return (index);
}
