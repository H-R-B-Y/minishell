/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:13:01 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_H
# define VEC3D_H

#include "defined.h"
# include <math.h>


// ██    ██ ███████  ██████ ██████  
// ██    ██ ██      ██           ██ 
// ██    ██ █████   ██       █████  
//  ██  ██  ██      ██           ██ 
//   ████   ███████  ██████ ██████  

typedef union s_vec3	t_vec3;

union __attribute__((aligned(8))) s_vec3
{
	struct
	{
		MYFLOAT	x;
		MYFLOAT	y;
		MYFLOAT	z;
	};
	MYFLOAT		v[3];
};

/**
 * @brief Add two 3D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The sum of the two vectors.
 */
t_vec3		vec3_add(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Calculate the angle between two 3D vectors in radians.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The angle between the two vectors in radians.
 */
MYFLOAT		vec3_angle(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Clamp a 3D vector's components between a min and max value.
 * @param vec The vector to clamp.
 * @param min The minimum values for each component.
 * @param max The maximum values for each component.
 * @return The clamped vector.
 */
t_vec3		vec3_clamp(t_vec3 vec, t_vec3 min, t_vec3 max);

/**
 * @brief Calculate the distance between two 3D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The distance between the two vectors.
 */
MYFLOAT		vec3_distance(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Divide a 3D vector by a scalar.
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return The result of the division.
 */
t_vec3		vec3_div_scalar(t_vec3 vec, MYFLOAT scalar);

/**
 * @brief Divide two 3D vectors element-wise.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The element-wise division result.
 */
t_vec3		vec3_div(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Calculate the dot product of two 3D vectors.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The dot product of the two vectors.
 */
MYFLOAT		vec3_dot_product(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Linearly interpolate between two 3D vectors.
 * @param start The start vector.
 * @param end The end vector.
 * @param t Interpolation factor (0.0 to 1.0).
 * @return The interpolated vector.
 */
t_vec3		vec3_lerp(t_vec3 start, t_vec3 end, MYFLOAT t);

/**
 * @brief Calculate the magnitude (length) of a 3D vector.
 * @param vec The vector.
 * @return The magnitude of the vector.
 */
MYFLOAT		vec3_magnitude(t_vec3 vec);

/**
 * @brief Multiply a 3D vector by a scalar.
 * @param vec The vector.
 * @param scalar The scalar value.
 * @return The scaled vector.
 */
t_vec3		vec3_mult_scalar(t_vec3 vec, MYFLOAT scalar);

/**
 * @brief Multiply two 3D vectors element-wise.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The element-wise multiplication result.
 */
t_vec3		vec3_mult(t_vec3 vec1, t_vec3 vec2);

/**
 * @brief Normalize a 3D vector.
 * @param vec The vector.
 * @return The normalized vector.
 */
t_vec3		vec3_normalise(t_vec3 vec);

/**
 * @brief Calculate a perpendicular vector to the given 3D vector.
 * @param vec The vector.
 * @return A vector perpendicular to the input.
 */
t_vec3		vec3_perpendicular(t_vec3 vec);

/**
 * @brief Project one 3D vector onto another.
 * @param vec The vector to project.
 * @param onto The vector onto which the projection is done.
 * @return The projection of `vec` onto `onto`.
 */
t_vec3		vec3_project(t_vec3 vec, t_vec3 onto);

/**
 * @brief Reflect a 3D vector across a normal.
 * @param vec The vector to reflect.
 * @param normal The normal vector.
 * @return The reflected vector.
 */
t_vec3		vec3_reflect(t_vec3 vec, t_vec3 normal);

/**
 * @brief Rotate a 3D vector by a given angle around a given axis.
 * @param vec The vector.
 * @param axis The axis of rotation (should be a unit vector).
 * @param angle The rotation angle in radians.
 * @return The rotated vector.
 */
t_vec3		vec3_rotate(t_vec3 vec, t_vec3 axis, MYFLOAT angle);

/**
 * @brief Subtract one 3D vector from another.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return The difference of the two vectors.
 */
t_vec3		vec3_sub(t_vec3 vec1, t_vec3 vec2);

#endif
