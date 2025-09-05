/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:16:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:43:15 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	ft_lstsize(t_list *lst)
{
	int		output;
	t_list	*index;

	output = 0;
	index = lst;
	while (index && ++output)
		index = index->next;
	return (output);
}
