/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpmc_ringbuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:49:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_mpmc_ringbuff.h"

t_mpmc_ringbuff	mpmc_rb_create(t_u32 capacity)
{
	return ((t_mpmc_ringbuff){
		.content = ft_calloc(capacity, sizeof(void *)),
		.capacity = capacity,
		.head = 0,
		.tail = 0,
		.size = 0
	});
}

void			mpmc_rb_destroy(t_mpmc_ringbuff *ringbuff)
{
	if (!ringbuff)
		return;
	free(ringbuff->content);
}
