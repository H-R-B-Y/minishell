/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_vec4	matrix4d_transform(t_matrix4d matrix, t_vec4 vec)
{
	t_vec4	result;

	result.x = matrix.x.x * vec.x + matrix.x.y * vec.y + matrix.x.z * vec.z + matrix.x.w * vec.w;
	result.y = matrix.y.x * vec.x + matrix.y.y * vec.y + matrix.y.z * vec.z + matrix.y.w * vec.w;
	result.z = matrix.z.x * vec.x + matrix.z.y * vec.y + matrix.z.z * vec.z + matrix.z.w * vec.w;
	result.w = matrix.w.x * vec.x + matrix.w.y * vec.y + matrix.w.z * vec.z + matrix.w.w * vec.w;
	return (result);
}
