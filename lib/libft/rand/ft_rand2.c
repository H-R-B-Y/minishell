/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand21.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:29:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 15:05:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rand.h"

static int	_xorshift(void)
{
	static int	seed = RANDSEED;

	seed ^= seed << XOR_A;
	seed ^= seed >> XOR_B;
	seed ^= seed << XOR_C;
	if (seed >= 0)
		return (seed);
	return (~seed + 1);
}

int	ft_rand2(int min, int max)
{
	int			this;

	this = _xorshift();
	this = (1 + this) % (max - min + 1);
	this += min;
	return (this);
}

/*
The problem with this is that the seed is defined at compile time.
I want to make a version that can take its own seed.
*/
