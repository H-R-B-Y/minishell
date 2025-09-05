/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_normalise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

t_vec2	vec2_normalise(t_vec2 vec)
{
	MYFLOAT	mag;

	mag = vec2_magnitude(vec);
	if (mag == 0)
		return ((t_vec2){0});
	return ((t_vec2){.x = (vec.x / mag),
		.y = (vec.y / mag)});
}
