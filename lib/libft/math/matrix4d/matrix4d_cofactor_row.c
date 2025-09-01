/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_cofactor_row.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:30:00 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 12:25:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

MYFLOAT	det3x3(MYFLOAT a11, MYFLOAT a12, MYFLOAT a13,
				MYFLOAT a21, MYFLOAT a22, MYFLOAT a23,
				MYFLOAT a31, MYFLOAT a32, MYFLOAT a33)
{
	return (a11 * (a22 * a33 - a23 * a32) - 
			a12 * (a21 * a33 - a23 * a31) + 
			a13 * (a21 * a32 - a22 * a31));
}

void	matrix4d_cofactor_row0(t_matrix4d matrix, t_vec4 *row, MYFLOAT det)
{
	row->x = det3x3(matrix.y.y, matrix.y.z, matrix.y.w,
					matrix.z.y, matrix.z.z, matrix.z.w,
					matrix.w.y, matrix.w.z, matrix.w.w) / det;
	row->y = -det3x3(matrix.x.y, matrix.x.z, matrix.x.w,
					matrix.z.y, matrix.z.z, matrix.z.w,
					matrix.w.y, matrix.w.z, matrix.w.w) / det;
	row->z = det3x3(matrix.x.y, matrix.x.z, matrix.x.w,
					matrix.y.y, matrix.y.z, matrix.y.w,
					matrix.w.y, matrix.w.z, matrix.w.w) / det;
	row->w = -det3x3(matrix.x.y, matrix.x.z, matrix.x.w,
					matrix.y.y, matrix.y.z, matrix.y.w,
					matrix.z.y, matrix.z.z, matrix.z.w) / det;
}

void	matrix4d_cofactor_row1(t_matrix4d matrix, t_vec4 *row, MYFLOAT det)
{
	row->x = -det3x3(matrix.y.x, matrix.y.z, matrix.y.w,
					matrix.z.x, matrix.z.z, matrix.z.w,
					matrix.w.x, matrix.w.z, matrix.w.w) / det;
	row->y = det3x3(matrix.x.x, matrix.x.z, matrix.x.w,
					matrix.z.x, matrix.z.z, matrix.z.w,
					matrix.w.x, matrix.w.z, matrix.w.w) / det;
	row->z = -det3x3(matrix.x.x, matrix.x.z, matrix.x.w,
					matrix.y.x, matrix.y.z, matrix.y.w,
					matrix.w.x, matrix.w.z, matrix.w.w) / det;
	row->w = det3x3(matrix.x.x, matrix.x.z, matrix.x.w,
					matrix.y.x, matrix.y.z, matrix.y.w,
					matrix.z.x, matrix.z.z, matrix.z.w) / det;
}

void	matrix4d_cofactor_row2(t_matrix4d matrix, t_vec4 *row, MYFLOAT det)
{
	row->x = det3x3(matrix.y.x, matrix.y.y, matrix.y.w,
					matrix.z.x, matrix.z.y, matrix.z.w,
					matrix.w.x, matrix.w.y, matrix.w.w) / det;
	row->y = -det3x3(matrix.x.x, matrix.x.y, matrix.x.w,
					matrix.z.x, matrix.z.y, matrix.z.w,
					matrix.w.x, matrix.w.y, matrix.w.w) / det;
	row->z = det3x3(matrix.x.x, matrix.x.y, matrix.x.w,
					matrix.y.x, matrix.y.y, matrix.y.w,
					matrix.w.x, matrix.w.y, matrix.w.w) / det;
	row->w = -det3x3(matrix.x.x, matrix.x.y, matrix.x.w,
					matrix.y.x, matrix.y.y, matrix.y.w,
					matrix.z.x, matrix.z.y, matrix.z.w) / det;
}

void	matrix4d_cofactor_row3(t_matrix4d matrix, t_vec4 *row, MYFLOAT det)
{
	row->x = -det3x3(matrix.y.x, matrix.y.y, matrix.y.z,
					matrix.z.x, matrix.z.y, matrix.z.z,
					matrix.w.x, matrix.w.y, matrix.w.z) / det;
	row->y = det3x3(matrix.x.x, matrix.x.y, matrix.x.z,
					matrix.z.x, matrix.z.y, matrix.z.z,
					matrix.w.x, matrix.w.y, matrix.w.z) / det;
	row->z = -det3x3(matrix.x.x, matrix.x.y, matrix.x.z,
					matrix.y.x, matrix.y.y, matrix.y.z,
					matrix.w.x, matrix.w.y, matrix.w.z) / det;
	row->w = det3x3(matrix.x.x, matrix.x.y, matrix.x.z,
					matrix.y.x, matrix.y.y, matrix.y.z,
					matrix.z.x, matrix.z.y, matrix.z.z) / det;
}
