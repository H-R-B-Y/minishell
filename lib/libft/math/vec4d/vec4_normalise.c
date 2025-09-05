/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_normalise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

t_vec4	vec4_normalise(t_vec4 vec)
{
	t_vec4	result;
	MYFLOAT	magnitude;

	magnitude = vec4_magnitude(vec);
	if (magnitude == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		result.w = 0;
	}
	else
	{
		result.x = vec.x / magnitude;
		result.y = vec.y / magnitude;
		result.z = vec.z / magnitude;
		result.w = vec.w / magnitude;
	}
	return (result);
}
