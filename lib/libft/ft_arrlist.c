/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurb <hurb@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:22 by hurb              #+#    #+#             */
/*   Updated: 2025/02/22 14:49:31 by hurb             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static inline void	do_nothing(void *v)
{
	(void)v;
	return ;
}

t_list	*ft_arrlist(void **chunks)
{
	t_list	*head;
	t_list	*tmp;

	if (!chunks || !*chunks)
		return ((void *)0);
	head = ft_lstnew(*chunks);
	chunks++;
	while (*chunks)
	{
		tmp = ft_lstnew(*chunks);
		if (!tmp)
		{
			ft_lstclear(&head, &do_nothing);
			return ((void *)0);
		}
		ft_lstadd_back(&head, tmp);
		chunks++;
	}
	return (head);
}
