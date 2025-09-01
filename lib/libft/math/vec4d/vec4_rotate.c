/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

t_vec4	vec4_rotate(t_vec4 vec, t_vec4 axis, MYFLOAT angle)
{
	t_vec4	result;
	MYFLOAT	cos_angle;
	MYFLOAT	sin_angle;
	MYFLOAT	dot_product;

	cos_angle = cosf(angle);
	sin_angle = sinf(angle);
	dot_product = vec4_dot_product(vec, axis);
	result.x = vec.x * cos_angle + axis.x * dot_product * (1 - cos_angle)
		+ (-axis.z * vec.y + axis.y * vec.z) * sin_angle;
	result.y = vec.y * cos_angle + axis.y * dot_product * (1 - cos_angle)
		+ (axis.z * vec.x - axis.x * vec.z) * sin_angle;
	result.z = vec.z * cos_angle + axis.z * dot_product * (1 - cos_angle)
		+ (-axis.y * vec.x + axis.x * vec.y) * sin_angle;
	result.w = vec.w;
	return (result);
}
