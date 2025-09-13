/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:50:28 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:30:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

int		heap_isfull(struct s_heap *heap)
{
	if (!heap)
		return (-1);
	if (heap->size >= heap->capacity)
		return (1);
	return (0);
}

int		heap_validindex(struct s_heap *heap, size_t index)
{
	if (!heap)
		return (-1);
	if (index < heap->size)
		return (1);
	return (0);
}
