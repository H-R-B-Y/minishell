/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

MYFLOAT	vec2_angle(t_vec2 vec1, t_vec2 vec2)
{
	MYFLOAT	dot_product;
	MYFLOAT	magnitude1;
	MYFLOAT	magnitude2;
	MYFLOAT	angle;

	dot_product = vec2_dot_product(vec1, vec2);
	magnitude1 = vec2_magnitude(vec1);
	magnitude2 = vec2_magnitude(vec2);
	if (magnitude1 == 0 || magnitude2 == 0)
		return (0);
	// Clamp the dot product to avoid numerical errors with acos
	dot_product = dot_product / (magnitude1 * magnitude2);
	if (dot_product > 1.0)
		dot_product = 1.0;
	else if (dot_product < -1.0)
		dot_product = -1.0;
	angle = acos(dot_product);
	return (angle);
}
