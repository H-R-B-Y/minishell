/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_rotate_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:55:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/04/04 13:02:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_rotate_x(MYFLOAT angle)
{
	t_matrix4d	matrix;
	MYFLOAT		cos_angle;
	MYFLOAT		sin_angle;

	cos_angle = cosf(angle);
	sin_angle = sinf(angle);
	matrix.x = (t_vec4){.x = 1.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f};
	matrix.y = (t_vec4){.x = 0.0f, .y = cos_angle, .z = -sin_angle, .w = 0.0f};
	matrix.z = (t_vec4){.x = 0.0f, .y = sin_angle, .z = cos_angle, 0.0f};
	matrix.w = (t_vec4){.x = 0.0f, .y = 0.0f, .z =  0.0f, .w = 1.0f};
	return (matrix);
}
