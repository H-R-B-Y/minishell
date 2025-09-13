/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:39:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:30:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

void			_heap_swapvalues(struct s_heap *heap, size_t index_a, size_t index_b)
{
	void	*data;

	if (!heap || index_a == index_b)
		return ;
	data = ft_calloc(heap->item_sz, 1);
	ft_memmove(data, heap->heap + (index_a * heap->item_sz), heap->item_sz);
	ft_memmove(heap->heap + (index_a * heap->item_sz),
		heap->heap + (index_b * heap->item_sz), heap->item_sz);
	ft_memmove(heap->heap + (index_b * heap->item_sz), data, heap->item_sz);
}

ssize_t			heap_parent_index(
	struct s_heap *heap,
	size_t child_index
)
{
	if (!heap || child_index > heap->size)
		return (-1);
	return((child_index - 1) / 2);
}

t_returncode	heap_children(
	struct s_heap *heap,
	size_t parent_indx,
	size_t *child_index1,
	size_t *child_index2
)
{
	if (!heap || parent_indx > heap->size
		|| !child_index1 || !child_index2)
		return (RETURN_ERROR);
	*child_index1 = (2 * parent_indx) + 1;
	*child_index2 = (2 * parent_indx) + 2;
	return (RETURN_OK);
}

void	*heap_at_index(struct s_heap *heap, size_t index)
{
	if (!heap || index > heap->size)
		return ((void *)0);
	return (heap->heap + (index * heap->item_sz));
}
