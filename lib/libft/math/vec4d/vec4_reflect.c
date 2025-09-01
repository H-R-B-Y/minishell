/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

t_vec4	vec4_reflect(t_vec4 vec, t_vec4 normal)
{
	t_vec4	result;
	MYFLOAT	dot_product;

	dot_product = vec4_dot_product(vec, normal);
	result.x = vec.x - 2 * dot_product * normal.x;
	result.y = vec.y - 2 * dot_product * normal.y;
	result.z = vec.z - 2 * dot_product * normal.z;
	result.w = vec.w - 2 * dot_product * normal.w;
	return (result);
}
