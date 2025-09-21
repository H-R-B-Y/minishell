/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:48:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 13:30:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"
#include <unistd.h>

void	write_heap(int fd, struct s_heap *heap, ssize_t	(*write_value)(int fd, void *buff))
{
	size_t	i;

	if (!heap || !write_value)
		return ;
	i = 0;
	while (i < heap->size)
	{
		write_value(fd, heap_at_index(heap, i));
		if (i != heap->size - 1)
			write(fd, ", ", 2);
		i++;
	}
}
