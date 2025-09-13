/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:35:01 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 12:57:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

struct s_heap	init_heap(
	size_t capacity,
	size_t item_sz,
	ssize_t (*compare)(void *a, void *b)
)
{
	return ((struct s_heap){
		.capacity = capacity,
		.item_sz = item_sz,
		.compare = compare,
		.heap = ft_calloc(capacity + 1, item_sz),
		.size = 0,
	});
}

void			destroy_heap(struct s_heap *heap)
{
	if (!heap)
		return ;
	if (heap->heap)
		free(heap->heap);
		
}
