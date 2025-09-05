/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_cdll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:27:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 12:27:03 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cdll.h"

static void	cdll_push_empty(t_cdll *list, struct s_cdll_node *node)
{
	node->next = node;
	node->prev = node;
	list->head = node;
	list->tail = node;
	list->count++;
}

size_t	cdll_push_front(t_cdll *list, struct s_cdll_node *node)
{
	if (!list || !node)
		return (0);
	if (list->count)
	{
		node->next = list->head;
		list->head->prev = node;
		node->prev = list->tail;
		list->tail->next = node;
		list->head = node;
		list->count++;
	}
	else
		cdll_push_empty(list, node);
	return (list->count);
}

size_t	cdll_push_back(t_cdll *list, struct s_cdll_node *node)
{
	if (!list || !node)
		return (0);
	if (list->count)
	{
		node->next = list->head;
		list->head->prev = node;
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
		list->count++;
	}
	else
		cdll_push_empty(list, node);
	return (list->count);
}
