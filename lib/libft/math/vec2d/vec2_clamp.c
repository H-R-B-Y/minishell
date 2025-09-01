/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_clamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

t_vec2	vec2_clamp(t_vec2 vec, t_vec2 min, t_vec2 max)
{
	t_vec2	clamped;

	clamped.x = fmaxf(min.x, fminf(vec.x, max.x));
	clamped.y = fmaxf(min.y, fminf(vec.y, max.y));
	return (clamped);
}