/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3d_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:35:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3d.h"

t_matrix3d	matrix3d_sub(t_matrix3d m1, t_matrix3d m2)
{
	t_matrix3d	result;

	result.x.x = m1.x.x - m2.x.x;
	result.x.y = m1.x.y - m2.x.y;
	result.x.z = m1.x.z - m2.x.z;
	result.y.x = m1.y.x - m2.y.x;
	result.y.y = m1.y.y - m2.y.y;
	result.y.z = m1.y.z - m2.y.z;
	result.z.x = m1.z.x - m2.z.x;
	result.z.y = m1.z.y - m2.z.y;
	result.z.z = m1.z.z - m2.z.z;
	return (result);
}
