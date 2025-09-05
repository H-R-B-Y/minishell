/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

t_vec2	vec2_reflect(t_vec2 vec, t_vec2 normal)
{
	t_vec2	result;
	MYFLOAT	dot_product;

	dot_product = vec2_dot_product(vec, normal);
	result.x = vec.x - 2 * dot_product * normal.x;
	result.y = vec.y - 2 * dot_product * normal.y;
	return (result);
}
