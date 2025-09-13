/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:59:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:31:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

t_returncode	heap_insert(struct s_heap *heap, void *value)
{
	if (!heap || !value)
		return (RETURN_ERROR);
	if (heap_isfull(heap))
		return (RETURN_ERROR);
	ft_memmove(heap->heap + (heap->size * heap->item_sz), value, heap->item_sz);
	heap->size += 1;
	heap_sift_up(heap, heap->size - 1);
	return (RETURN_OK);
}
