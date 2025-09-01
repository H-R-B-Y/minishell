/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:18:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec4d.h"

t_vec4	vec4_clamp(t_vec4 vec, t_vec4 min, t_vec4 max)
{
	t_vec4	clamped;

	clamped.x = fmaxf(min.x, fminf(vec.x, max.x));
	clamped.y = fmaxf(min.y, fminf(vec.y, max.y));
	clamped.z = fmaxf(min.z, fminf(vec.z, max.z));
	clamped.w = fmaxf(min.w, fminf(vec.w, max.w));
	return (clamped);
}
