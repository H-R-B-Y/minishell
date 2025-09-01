/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:29:00 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/28 12:27:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

MYFLOAT	normalize(MYFLOAT from, MYFLOAT too, MYFLOAT t)
{
	MYFLOAT	range;
	
	range = too - from;
	if (range == 0)
		return (0);
	return ((t - from) / range);
}
