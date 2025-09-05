/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maprange.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:11:21 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

MYFLOAT	maprange(t_vec2 from, t_vec2 too, MYFLOAT t)
{
	MYFLOAT	tn;
	MYFLOAT	from_range;

	from_range = from.y - from.x;
	if (from_range == 0)
		return (too.x);
	tn = (t - from.x) / from_range;
	return (too.x + tn * (too.y - too.x));
}
