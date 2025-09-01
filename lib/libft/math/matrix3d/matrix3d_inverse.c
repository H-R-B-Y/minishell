/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3d_inverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:35:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3d.h"

t_matrix3d	matrix3d_inverse(t_matrix3d mat)
{
	t_matrix3d	result;
	MYFLOAT		det;

	det = matrix3d_determinant(mat);
	if (det == 0)
		return ((t_matrix3d){0});
	result.x.x = (mat.y.y * mat.z.z - mat.y.z * mat.z.y) / det;
	result.x.y = (mat.x.z * mat.z.y - mat.x.y * mat.z.z) / det;
	result.x.z = (mat.x.y * mat.y.z - mat.x.z * mat.y.y) / det;
	result.y.x = (mat.y.z * mat.z.x - mat.y.x * mat.z.z) / det;
	result.y.y = (mat.x.x * mat.z.z - mat.x.z * mat.z.x) / det;
	result.y.z = (mat.x.z * mat.y.x - mat.x.x * mat.y.z) / det;
	result.z.x = (mat.y.x * mat.z.y - mat.y.y * mat.z.x) / det;
	result.z.y = (mat.x.y * mat.z.x - mat.x.x * mat.z.y) / det;
	result.z.z = (mat.x.x * mat.y.y - mat.x.y * mat.y.x) / det;
	return (result);
}
