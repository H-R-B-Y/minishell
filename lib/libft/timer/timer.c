/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:53:51 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/13 13:52:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_timer.h"

t_mstime	time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0) == -1)
		(void)!write(2, "gettimeofday() error\n", 22);
	return ((t_mstime)(time.tv_sec * 1000000UL + time.tv_usec));
}

static t_mstime	*this_timer(void)
{
	static t_mstime	time[TIMER_MAX] = {0};
	
	return ((void *)time);
}

ssize_t	start_timer(void)
{
	static size_t	timer = 0;

	if (timer == TIMER_MAX)
		return (-1);
	this_timer()[timer] = time_in_ms();
	return (timer++);
}

void	reset_timer(size_t timer)
{
	if (timer >= TIMER_MAX)
		return ;
	this_timer()[timer] = time_in_ms();
}

t_mstime	end_timer(size_t timer)
{
	if (timer >= TIMER_MAX)
		return (0);
	return (time_in_ms() - this_timer()[timer]);
}

