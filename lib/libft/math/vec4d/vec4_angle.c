/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_angle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

MYFLOAT	vec4_angle(t_vec4 a, t_vec4 b)
{
	MYFLOAT	dot_product;
	MYFLOAT	magnitude_a;
	MYFLOAT	magnitude_b;

	dot_product = vec4_dot_product(a, b);
	magnitude_a = vec4_magnitude(a);
	magnitude_b = vec4_magnitude(b);
	if (magnitude_a == 0 || magnitude_b == 0)
		return (0);
	// Clamp the dot product to avoid numerical errors with acos
	dot_product = dot_product / (magnitude_a * magnitude_b);
	if (dot_product > 1.0)
		dot_product = 1.0;
	else if (dot_product < -1.0)
		dot_product = -1.0;
	return (acosf(dot_product));
}
