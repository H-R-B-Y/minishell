/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:32:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_add(t_matrix4d a, t_matrix4d b)
{
	t_matrix4d	result;

	result.x = vec4_add(a.x, b.x);
	result.y = vec4_add(a.y, b.y);
	result.z = vec4_add(a.z, b.z);
	result.w = vec4_add(a.w, b.w);
	return (result);
}
