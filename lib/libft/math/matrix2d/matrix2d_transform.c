/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2d_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:29:01 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:38:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix2d.h"

t_vec2	matrix2d_transform(t_matrix2d mat, t_vec2 vec)
{
	t_vec2	result;

	result.x = mat.x.x * vec.x + mat.x.y * vec.y;
	result.y = mat.y.x * vec.x + mat.y.y * vec.y;
	return (result);
}
