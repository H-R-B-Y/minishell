/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:57:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2d.h"

MYFLOAT	vec2_distance(t_vec2 vec1, t_vec2 vec2)
{
	t_vec2	difference;

	difference = vec2_mult_scalar(vec2, -1.0f);
	difference = vec2_add(vec1, difference);
	return (vec2_magnitude(difference));
}
