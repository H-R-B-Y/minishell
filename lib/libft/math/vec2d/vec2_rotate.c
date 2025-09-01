/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

t_vec2	vec2_rotate(t_vec2 vec, MYFLOAT angle)
{
	t_vec2	rotated;
	MYFLOAT	radians;

	radians = angle * (M_PI / 180.0);
	rotated.x = vec.x * cos(radians) - vec.y * sin(radians);
	rotated.y = vec.x * sin(radians) + vec.y * cos(radians);
	return (rotated);
}
