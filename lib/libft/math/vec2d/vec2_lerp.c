/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_lerp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

t_vec2	vec2_lerp(t_vec2 vec1, t_vec2 vec2, MYFLOAT t)
{
	t_vec2	result;

	if (t < 0)
		t = 0;
	else if (t > 1)
		t = 1;
	result.x = vec1.x + (vec2.x - vec1.x) * t;
	result.y = vec1.y + (vec2.y - vec1.y) * t;
	return (result);
}