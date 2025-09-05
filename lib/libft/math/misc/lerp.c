/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:06:36 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:07:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

MYFLOAT	lerp(MYFLOAT start, MYFLOAT end, MYFLOAT t)
{
	return ((1.0f - t) * start + t * end);
}
