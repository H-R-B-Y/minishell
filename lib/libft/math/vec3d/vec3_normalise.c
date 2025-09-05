/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:17:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:44 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3	vec3_normalise(t_vec3 vec)
{
	MYFLOAT	magnitude;

	magnitude = vec3_magnitude(vec);
	if (magnitude == 0)
		return ((t_vec3){0});
	return ((t_vec3){.x = vec.x / magnitude,
		.y = vec.y / magnitude,
		.z = vec.z / magnitude});
}
