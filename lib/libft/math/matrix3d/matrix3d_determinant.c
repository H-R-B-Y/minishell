/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3d_determinant.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:35:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3d.h"

MYFLOAT	matrix3d_determinant(t_matrix3d mat)
{
	MYFLOAT	det;

	det = mat.x.x * (mat.y.y * mat.z.z - mat.y.z * mat.z.y)
		- mat.x.y * (mat.y.x * mat.z.z - mat.y.z * mat.z.x)
		+ mat.x.z * (mat.y.x * mat.z.y - mat.y.y * mat.z.x);
	return (det);
}
