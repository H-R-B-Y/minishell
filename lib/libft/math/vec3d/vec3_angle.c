/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:17:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

MYFLOAT	vec3_angle(t_vec3 vec1, t_vec3 vec2)
{
	MYFLOAT	dot_product;
	MYFLOAT	magnitude1;
	MYFLOAT	magnitude2;
	MYFLOAT	angle;

	dot_product = vec3_dot_product(vec1, vec2);
	magnitude1 = vec3_magnitude(vec1);
	magnitude2 = vec3_magnitude(vec2);
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
