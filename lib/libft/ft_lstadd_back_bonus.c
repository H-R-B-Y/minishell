/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:19:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/02 17:17:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*index;

	if (!new_node || !lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	index = ft_lstlast(*lst);
	if (!index)
		return ;
	index->next = new_node;
}
