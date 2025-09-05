/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:23:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

MYFLOAT	vec4_distance(t_vec4 vec1, t_vec4 vec2)
{
	MYFLOAT	dx;
	MYFLOAT	dy;
	MYFLOAT	dz;
	MYFLOAT	dw;

	dx = vec2.x - vec1.x;
	dy = vec2.y - vec1.y;
	dz = vec2.z - vec1.z;
	dw = vec2.w - vec1.w;
	return (sqrtf(dx * dx + dy * dy + dz * dz + dw * dw));
}
