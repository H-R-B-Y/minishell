/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpmc_ringbuff_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:37:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 11:56:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mpmc_ringbuff.h"

u64				mpmc_rb_size(t_mpmc_ringbuff *ringbuff)
{
	if (!ringbuff)
		return (0);
	return (__atomic_load_n(&ringbuff->size, __ATOMIC_ACQUIRE));
}
