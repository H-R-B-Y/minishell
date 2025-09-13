/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heapify.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:26:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:32:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

t_returncode	heapify(struct s_heap *heap)
{
	ssize_t	parent;

	if (!heap)
		return (RETURN_ERROR);
	if (heap->size <= 1)
		return (RETURN_OK);
	parent = heap_parent_index(heap, heap->size - 1);
	while (heap_validindex(heap, parent) && parent >= 0)
	{
		heap_sift_down(heap, parent);
		parent--;
	}
	return (RETURN_OK);
}