/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_scaling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/04/04 13:04:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_scaling(MYFLOAT scale_x, MYFLOAT scale_y, MYFLOAT scale_z, MYFLOAT scale_w)
{
	t_matrix4d	matrix;

	matrix.x = (t_vec4){.x = scale_x, 0.0f, 0.0f, 0.0f};
	matrix.y = (t_vec4){.x = 0.0f, scale_y, 0.0f, 0.0f};
	matrix.z = (t_vec4){.x = 0.0f, 0.0f, scale_z, 0.0f};
	matrix.w = (t_vec4){.x = 0.0f, 0.0f, 0.0f, scale_w};
	return (matrix);
}
