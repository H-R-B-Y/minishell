/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:32:05 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2D_H
# define VEC2D_H

#include "defined.h"
# include <math.h>

// ██    ██ ███████  ██████ ██████  
// ██    ██ ██      ██           ██ 
// ██    ██ █████   ██       █████  
//  ██  ██  ██      ██      ██      
//   ████   ███████  ██████ ███████ 

typedef union s_vec2	t_vec2;

union __attribute__((aligned(8))) s_vec2
{
	struct
	{
		MYFLOAT	x;
		MYFLOAT	y;
	};
	MYFLOAT		v[2];
};

/**
 * @brief Calculate the magnitude of a 2D vector.
 * @param vec The vector.
 * @return The magnitude of the vector.
 */
MYFLOAT		vec2_magnitude(t_vec2 vec);

/**
 * @brief Calculate the dot product of two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The dot product of the two vectors.
 */
MYFLOAT		vec2_dot_product(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Normalize a 2D vector.
 * @param vec The vector.
 * @return The normalized vector.
 */
t_vec2		vec2_normalise(t_vec2 vec);

/**
 * @brief Add two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The sum of the two vectors.
 */
t_vec2		vec2_add(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Rotate a 2D vector by a given angle.
 * @param vec The vector to be rotated.
 * @param angle The rotation angle in degrees.
 * @return The rotated vector.
 */
t_vec2		vec2_rotate(t_vec2 vec, MYFLOAT angle);

/**
 * @brief Multiply a 2D vector by a scalar.
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec2		vec2_mult_scalar(t_vec2 vec, MYFLOAT scalar);

/**
 * @brief Multiply two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The product of the two vectors.
 */
t_vec2		vec2_mult(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Subtract two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The difference of the two vectors.
 */
t_vec2		vec2_sub(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Divide two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The quotient of the two vectors.
 * Note: This function performs element-wise division.
 */
t_vec2		vec2_div(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Divide a 2D vector by a scalar.
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return The quotient of the vector and the scalar.
 */
t_vec2		vec2_div_scalar(t_vec2 vec, MYFLOAT scalar);

/**
 * @brief Returns the perpendicular vector of a 2D vector.
 * @param vec The vector.
 * @return The perpendicular vector.
 */
t_vec2		vec2_perpendicular(t_vec2 vec);

/**
 * @brief Calculate the angle between two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The angle in radians.
 */
MYFLOAT		vec2_angle(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Reflect a 2D vector across a normal vector.
 * @param vec The vector to be reflected.
 * @param normal The normal vector.
 * @return The reflected vector.
 */
t_vec2		vec2_reflect(t_vec2 vec, t_vec2 normal);

/**
 * @brief Project a 2D vector onto another vector.
 * @param vec1 The vector to be projected.
 * @param vec2 The vector onto which vec1 is projected.
 * @return The projected vector.
 */
t_vec2		vec2_project(t_vec2 vec1, t_vec2 vec2);

/**
 * @brief Linearly interpolate between two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @param t The interpolation factor (0.0 to 1.0).
 * @return The interpolated vector.
 */
t_vec2		vec2_lerp(t_vec2 vec1, t_vec2 vec2, MYFLOAT t);

/**
 * @brief Calculate the distance between two 2D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The distance between the two vectors.
 */
MYFLOAT		vec2_distance(t_vec2 vec1, t_vec2 vec2);


/**
 * @brief Clamp a 2D vector between two other vectors.
 * @param vec The vector to be clamped.
 * @param min The minimum vector.
 * @param max The maximum vector.
 * @return The clamped vector.
 * Note: This function clamps each component of the vector independently.
 */
t_vec2	vec2_clamp(t_vec2 vec, t_vec2 min, t_vec2 max);

# endif