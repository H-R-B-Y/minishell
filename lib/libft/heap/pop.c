/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:18:42 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:31:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

void	*heap_pop(struct s_heap *heap)
{
	void	*data;

	if (!heap || heap->size == 0)
		return ((void *)0);
	if (heap->size == 1)
	{
		heap->size--;
		return (heap->heap);
	}
	_heap_swapvalues(heap, 0, heap->size - 1);
	heap->size--;
	heap_sift_down(heap, 0);
	data = heap_at_index(heap, heap->size);
	return (data);
}
