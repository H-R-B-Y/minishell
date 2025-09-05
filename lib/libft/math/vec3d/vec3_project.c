/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:17:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3	vec3_project(t_vec3 vec, t_vec3 onto)
{
	t_vec3	projected;
	MYFLOAT	dot_product;
	MYFLOAT	magnitude_squared;

	dot_product = vec3_dot_product(vec, onto);
	magnitude_squared = vec3_dot_product(onto, onto);
	if (magnitude_squared == 0)
		return ((t_vec3){0});
	projected.x = (dot_product / magnitude_squared) * onto.x;
	projected.y = (dot_product / magnitude_squared) * onto.y;
	projected.z = (dot_product / magnitude_squared) * onto.z;
	return (projected);
}
