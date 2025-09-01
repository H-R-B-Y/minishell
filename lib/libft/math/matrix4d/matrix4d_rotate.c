/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:55:29 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:42:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_rotate(MYFLOAT x_angle, MYFLOAT y_angle, MYFLOAT z_angle)
{
	t_matrix4d	angles[4];

	angles[0] = matrix4d_rotate_x(x_angle);
	angles[1] = matrix4d_rotate_y(y_angle);
	angles[2] = matrix4d_rotate_z(z_angle);
	angles[0] = matrix4d_multiply(angles[0], angles[1]);
	angles[3] = matrix4d_multiply(angles[0], angles[2]);
	return (angles[3]);
}
