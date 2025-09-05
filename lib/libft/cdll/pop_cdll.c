/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_cdll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:36:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 12:27:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cdll.h"

struct s_cdll_node	*cdll_pop_front(t_cdll *list)
{
	struct s_cdll_node	*out;

	if (!list || list->count == 0)
		return ((void *)0);
	out = list->head;
	if (list->count > 1)
	{
		list->head = out->next;
		list->head->prev = list->tail;
		list->tail->next = list->head;
	}
	else
	{
		list->head = 0;
		list->tail = 0;
	}
	out->next = 0;
	out->prev = 0;
	list->count--;
	return (out);
}

struct s_cdll_node	*cdll_pop_back(t_cdll *list)
{
	struct s_cdll_node	*out;

	if (!list || list->count == 0)
		return ((void *)0);
	out = list->tail;
	if (list->count > 1)
	{
		list->tail = out->prev;
		list->head->prev = list->tail;
		list->tail->next = list->head;
	}
	else
	{
		list->head = 0;
		list->tail = 0;
	}
	out->next = 0;
	out->prev = 0;
	list->count--;
	return (out);
}
