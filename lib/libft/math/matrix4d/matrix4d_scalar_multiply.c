/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_scalar_multiply.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:55:36 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_scalar_multiply(t_matrix4d matrix, MYFLOAT scalar)
{
	t_matrix4d	result;

	result.x.x = matrix.x.x * scalar;
	result.x.y = matrix.x.y * scalar;
	result.x.z = matrix.x.z * scalar;
	result.x.w = matrix.x.w * scalar;
	result.y.x = matrix.y.x * scalar;
	result.y.y = matrix.y.y * scalar;
	result.y.z = matrix.y.z * scalar;
	result.y.w = matrix.y.w * scalar;
	result.z.x = matrix.z.x * scalar;
	result.z.y = matrix.z.y * scalar;
	result.z.z = matrix.z.z * scalar;
	result.z.w = matrix.z.w * scalar;
	result.w.x = matrix.w.x * scalar;
	result.w.y = matrix.w.y * scalar;
	result.w.z = matrix.w.z * scalar;
	result.w.w = matrix.w.w * scalar;
	return (result);
}
