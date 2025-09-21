/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 14:55:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 15:05:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rand.h"

static int *_get_seed_ptr(void)
{
	static int	seed = RANDSEED;

	return (&seed);
}

void	ft_srand(int seed)
{
	int	*seed_ptr;

	seed_ptr = _get_seed_ptr();
	*seed_ptr = seed;
}

static int	_xorshift(void)
{
	int	*seed_ptr;

	seed_ptr = _get_seed_ptr();
	*seed_ptr ^= *seed_ptr << XOR_A;
	*seed_ptr ^= *seed_ptr >> XOR_B;
	*seed_ptr ^= *seed_ptr << XOR_C;
	if (*seed_ptr >= 0)
		return (*seed_ptr);
	return (~(*seed_ptr) + 1);
}

int	ft_rand(int min, int max)
{
	int			this;

	this = _xorshift();
	this = (1 + this) % (max - min + 1);
	this += min;
	return (this);
}

