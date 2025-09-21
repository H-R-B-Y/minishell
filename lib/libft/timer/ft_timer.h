/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 12:57:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/13 13:09:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_TIMER_H
# define FT_TIMER_H

# define TIMER_MAX 1024

# include <sys/time.h>
# include <unistd.h>
# include "defined.h"


typedef t_u64	t_mstime;

ssize_t	start_timer(void);
void	reset_timer(size_t timer);
t_mstime	end_timer(size_t timer);

#endif
