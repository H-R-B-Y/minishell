/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sift_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:53:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:30:58 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

t_returncode	heap_sift_up(struct s_heap *heap, size_t child_index)
{
	size_t	parent;

	if (!heap || !heap_validindex(heap, child_index))
		return (RETURN_ERROR);
	parent = heap_parent_index(heap, child_index);
	while (heap_validindex(heap, parent)
		&& heap->compare(heap_at_index(heap, parent),
			heap_at_index(heap, child_index)) > 0)
	{
		_heap_swapvalues(heap, child_index, parent);
		child_index = parent;
		parent = heap_parent_index(heap, child_index);
	}
	return (RETURN_OK);
}
