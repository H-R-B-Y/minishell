/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mpmc_ringbuff.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:47:42 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 11:56:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __GNU_SOURCE
#  define __GNU_SOURCE
# endif

#ifndef FT_MPMC_RINGBUFF_H
# define FT_MPMC_RINGBUFF_H

# include "ft_mem.h"
# include "defined.h"

# ifndef MPMC_RINGBUFF_SZ
#  define MPMC_RINGBUFF_SZ 1024
# endif

typedef struct s_mpmc_ringbuff	t_mpmc_ringbuff;
struct s_mpmc_ringbuff
{
	void	*content[MPMC_RINGBUFF_SZ];
	vu32	head;
	vu32	tail;
	vu32	size;
};

/**
 * @brief initialise a new ringbuffer
 * 
 * @note: just returns the default values in a struct for copying
 * 
 * @return t_mpmc_ringbuff 
 */
t_mpmc_ringbuff	mpmc_rb_create(void);

/**
 * @brief Destory a ring buffer
 * 
 * @note: Not sure if this should take any destructor
 * functions for the contents of the nodes
 * 
 * @param ringbuff 
 */
void			mpmc_rb_destroy(t_mpmc_ringbuff *ringbuff);

int				mpmc_rb_push(t_mpmc_ringbuff *ringbuff, void *content);
int				mpmc_rb_pop(t_mpmc_ringbuff *ringbuff, void **content);

u64				mpmc_rb_size(t_mpmc_ringbuff *s_mpmc_ringbuff);

#endif
