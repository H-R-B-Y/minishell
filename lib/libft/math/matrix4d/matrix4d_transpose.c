/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_transpose.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:57:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:42:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_transpose(t_matrix4d matrix)
{
	t_matrix4d	result;

	result.x.x = matrix.x.x;
	result.x.y = matrix.y.x;
	result.x.z = matrix.z.x;
	result.x.w = matrix.w.x;
	result.y.x = matrix.x.y;
	result.y.y = matrix.y.y;
	result.y.z = matrix.z.y;
	result.y.w = matrix.w.y;
	result.z.x = matrix.x.z;
	result.z.y = matrix.y.z;
	result.z.z = matrix.z.z;
	result.z.w = matrix.w.z;
	result.w.x = matrix.x.w;
	result.w.y = matrix.y.w;
	result.w.z = matrix.z.w;
	result.w.w = matrix.w.w;
	return (result);
}
