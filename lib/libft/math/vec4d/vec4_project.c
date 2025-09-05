/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

t_vec4	vec4_project(t_vec4 vec1, t_vec4 vec2)
{
	MYFLOAT	dot_product;
	MYFLOAT	magnitude_squared;
	t_vec4	result;

	dot_product = vec4_dot_product(vec1, vec2);
	magnitude_squared = vec4_dot_product(vec2, vec2);
	if (magnitude_squared == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		result.w = 0;
	}
	else
	{
		result.x = (dot_product / magnitude_squared) * vec2.x;
		result.y = (dot_product / magnitude_squared) * vec2.y;
		result.z = (dot_product / magnitude_squared) * vec2.z;
		result.w = (dot_product / magnitude_squared) * vec2.w;
	}
	return (result);
}
