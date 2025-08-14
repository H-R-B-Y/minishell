/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:07:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:50:20 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_lstpop_back(t_list **lst)
{
	t_list	*node;
	t_list	*last_node;

	if (!lst || !*lst)
		return ((void *)0);
	node = *lst;
	if (!(*lst)->next)
		*lst = 0;
	else
	{
		while (node->next)
		{
			last_node = node;
			node = node->next;
		}
		last_node->next = 0;
	}
	return (node);
}

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return ((void *)0);
	node = *lst;
	*lst = node->next;
	node->next = 0;
	return (node);
}
