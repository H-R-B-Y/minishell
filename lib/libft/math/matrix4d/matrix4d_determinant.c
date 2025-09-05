/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_determinant.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:32:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:42:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

MYFLOAT	matrix4d_determinant(t_matrix4d matrix)
{
	return (
		matrix.x.x * (matrix.y.y * matrix.z.z * matrix.w.w
			+ matrix.y.z * matrix.z.w * matrix.w.y
			+ matrix.y.w * matrix.z.y * matrix.w.z
			- matrix.y.w * matrix.z.z * matrix.w.y
			- matrix.y.z * matrix.z.y * matrix.w.w
			- matrix.y.y * matrix.z.w * matrix.w.z)
		- matrix.x.y * (matrix.y.x * matrix.z.z * matrix.w.w
			+ matrix.y.z * matrix.z.w * matrix.w.x
			+ matrix.y.w * matrix.z.x * matrix.w.z
			- matrix.y.w * matrix.z.z * matrix.w.x
			- matrix.y.z * matrix.z.x * matrix.w.w
			- matrix.y.x * matrix.z.w * matrix.w.z)
		+ matrix.x.z * (matrix.y.x * matrix.z.y * matrix.w.w
			+ matrix.y.y * matrix.z.w * matrix.w.x
			+ matrix.y.w * matrix.z.x * matrix.w.y
			- matrix.y.w * matrix.z.y * matrix.w.x
			- matrix.y.y * matrix.z.x * matrix.w.w
			- matrix.y.x * matrix.z.w * matrix.w.y)
		- matrix.x.w * (matrix.y.x * matrix.z.y * matrix.w.z
			+ matrix.y.y * matrix.z.z * matrix.w.x
			+ matrix.y.z * matrix.z.x * matrix.w.y
			- matrix.y.z * matrix.z.y * matrix.w.x
			- matrix.y.y * matrix.z.x * matrix.w.z
			- matrix.y.x * matrix.z.z * matrix.w.y));
}
