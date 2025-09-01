/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:17:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:26:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3d.h"

t_vec3	vec3_clamp(t_vec3 vec, t_vec3 min, t_vec3 max)
{
	t_vec3	clamped;

	clamped.x = fmaxf(min.x, fminf(vec.x, max.x));
	clamped.y = fmaxf(min.y, fminf(vec.y, max.y));
	clamped.z = fmaxf(min.z, fminf(vec.z, max.z));
	return (clamped);
}

