/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdll_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:07:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 12:27:03 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cdll.h"

struct s_cdll_node *cdll_get(t_cdll *list, size_t i)
{
	struct s_cdll_node *tmp;

	if (!list || !list->head || list->count == 0)
		return (NULL);
	tmp = list->head;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	return (tmp);
}
