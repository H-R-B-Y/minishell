/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_inverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:32:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 12:24:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_inverse(t_matrix4d matrix)
{
	t_matrix4d	inv;
	MYFLOAT		det;

	det = matrix4d_determinant(matrix);
	if (det == 0.0f)
		return (matrix4d_identity());
	matrix4d_cofactor_row0(matrix, &inv.x, det);
	matrix4d_cofactor_row1(matrix, &inv.y, det);
	matrix4d_cofactor_row2(matrix, &inv.z, det);
	matrix4d_cofactor_row3(matrix, &inv.w, det);
	return (inv);
}

