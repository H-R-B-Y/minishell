/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpmc_ringbuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:16:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 11:56:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_mpmc_ringbuff.h"

t_mpmc_ringbuff	mpmc_rb_create(void)
{
	t_mpmc_ringbuff	buff = {0};

	return (buff);
}

void			mpmc_rb_destroy(t_mpmc_ringbuff *ringbuff)
{
	(void)ringbuff;
}
