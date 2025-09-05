/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4d_identity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:32:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/04/04 13:01:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix4d.h"

t_matrix4d	matrix4d_identity(void)
{
	t_matrix4d	matrix;

	matrix.x = (t_vec4){.x = 1.0f, .y = 0.0f, .z = 0.0f, .w = 0.0f};
	matrix.y = (t_vec4){.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = 0.0f};
	matrix.z = (t_vec4){.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = 0.0f};
	matrix.w = (t_vec4){.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f};
	return (matrix);
}
