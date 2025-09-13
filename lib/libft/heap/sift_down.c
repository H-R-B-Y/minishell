/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sift_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:03:28 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:31:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

t_returncode	heap_sift_down(struct s_heap *heap, size_t parent)
{
	size_t	children[2];

	if (!heap || !heap_validindex(heap, parent))
		return (RETURN_ERROR);
	if (heap_children(heap, parent,
		&children[0], &children[1]) != RETURN_OK)
		return (RETURN_ERROR);
	if (!heap_validindex(heap, children[0])
		&& !heap_validindex(heap, children[1]))
		return (RETURN_OK);
	if (heap_validindex(heap, children[1]))
	{
		if (heap->compare(
			heap_at_index(heap, children[0]),
			heap_at_index(heap, children[1])) > 0)
			children[0] = children[1];
	}
	if (!(heap->compare(
		heap_at_index(heap, parent),
		heap_at_index(heap, children[0])) > 0))
		return (RETURN_OK);
	_heap_swapvalues(heap, children[0], parent);
	heap_sift_down(heap, children[0]);
	return (RETURN_OK);
}
