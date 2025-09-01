/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:27:21 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:00:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*index;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (0);
	output = ft_lstnew(f(lst->content));
	if (!output)
		return (0);
	index = lst;
	while (index->next)
	{
		index = index->next;
		tmp = ft_lstnew(f(index->content));
		if (!tmp)
		{
			ft_lstclear(&output, del);
			return (0);
		}
		ft_lstadd_back(&output, tmp);
	}
	return (output);
}
