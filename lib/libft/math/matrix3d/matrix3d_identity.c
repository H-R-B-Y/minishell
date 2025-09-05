/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3d_identity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:35:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/04/03 20:36:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix3d.h"

t_matrix3d	matrix3d_identity(void)
{
	t_matrix3d	result;

	result.x.x = 1.0f;
	result.x.y = 0.0f;
	result.x.z = 0.0f;
	result.y.x = 0.0f;
	result.y.y = 1.0f;
	result.y.z = 0.0f;
	result.z.x = 0.0f;
	result.z.y = 0.0f;
	result.z.z = 1.0f;
	return (result);
}
