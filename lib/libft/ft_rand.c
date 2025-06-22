/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:29:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/22 15:26:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	_xorshift()
{
	static int	seed = RANDSEED;

	seed ^= seed << 13;
	seed ^= seed >> 15;
	seed ^= seed << 5;
	if (seed >= 0)
		return (seed);
	return (~seed + 1);
}

int	ft_rand(int min, int max)
{
	int			this;

	this = _xorshift();
	this = (1 + this) % (max - min + 1);
	this += min;
	return (this);
}

// # include <stdio.h>
// int main ()
// {
// 	int	c;

// 	while (1)
// 	{
// 		c = ft_rand(0, 10);
// 		printf("%d\n", c);
// 		if (c == 10)
// 			break ;
// 	}
// 	return (0);
// }
