/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3d_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:35:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3d.h"

t_vec3	matrix3d_transform(t_matrix3d mat, t_vec3 vec)
{
	t_vec3	result;

	result.x = mat.x.x * vec.x + mat.x.y * vec.y + mat.x.z * vec.z;
	result.y = mat.y.x * vec.x + mat.y.y * vec.y + mat.y.z * vec.z;
	result.z = mat.z.x * vec.x + mat.z.y * vec.y + mat.z.z * vec.z;
	return (result);
}

