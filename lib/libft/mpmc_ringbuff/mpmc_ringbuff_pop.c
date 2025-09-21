/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpmc_ringbuff_pop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:19:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:49:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mpmc_ringbuff.h"

int				mpmc_rb_pop(t_mpmc_ringbuff *ringbuff, void **content)
{
	t_u32		head;
	void	*stolen;

	if (!ringbuff || !content)
		return (RETURN_ERROR);
	head = __atomic_fetch_add(&ringbuff->head, 1, __ATOMIC_ACQ_REL);
	stolen = __atomic_exchange_n(
		&ringbuff->content[head % ringbuff->capacity],
		NULL, __ATOMIC_ACQ_REL);
	if (stolen != NULL)
	{
		*content = stolen;
		__atomic_fetch_sub(&ringbuff->size, 1, __ATOMIC_ACQ_REL);
		return (RETURN_OK);
	}
	__atomic_fetch_sub(&ringbuff->head, 1, __ATOMIC_ACQ_REL);
	return (RETURN_ERROR);
}

