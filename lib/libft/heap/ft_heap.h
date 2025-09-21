/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:27:06 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:31:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "ft_mem.h"
# include "defined.h"

struct s_heap
{
	void	*heap;
	size_t	item_sz; // size of individual item
	size_t	size; // count of items in heap
	size_t	capacity; // max items in heap

	ssize_t	(*compare)(void *a, void *b);
};

/**
 * @brief Initialise a new heap, array will be shallow copied
 * 
 * @param capacity Maximum items in array
 * @param item_sz Size of individual items in array
 * @return struct s_heap new stuct populated with data
 */
struct s_heap	init_heap(size_t capacity, size_t item_sz,
				ssize_t (*compare)(void *a, void *b));

void			destroy_heap(struct s_heap *heap);

// private
void			_heap_swapvalues(struct s_heap *heap, size_t index_a, size_t index_b);
ssize_t			heap_parent_index(struct s_heap *heap, size_t child_index);
t_returncode	heap_children(struct s_heap *heap, size_t parent_indx, size_t *child_index1, size_t	*child_index2);

void			*heap_at_index(struct s_heap *heap, size_t index);
int				heap_isfull(struct s_heap *heap);
int				heap_validindex(struct s_heap *heap, size_t index);

t_returncode	heap_sift_up(struct s_heap *heap, size_t child_index);
t_returncode	heap_sift_down(struct s_heap *heap, size_t parent);
t_returncode	heap_insert(struct s_heap *heap, void *value);

void			*heap_pop(struct s_heap *heap);

t_returncode	heapify(struct s_heap *heap);

#endif
