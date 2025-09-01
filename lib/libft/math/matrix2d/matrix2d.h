/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:27:25 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:57:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "defined.h"
#include <math.h>
#include "vec2d.h"  // Assuming you have vec2d operations in this header.

typedef union s_matrix2d
{

	struct 
	{
		t_vec2 x;  // First row (x values)
		t_vec2 y;  // Second row (y values)
	};
	struct 
	{
		MYFLOAT x1, y1;  // First row elements
		MYFLOAT x2, y2;  // Second row elements
	};
	MYFLOAT m[2][2];  // 2D array representation
} __attribute__((aligned(8))) t_matrix2d;

// Function declarations

/**
 * @brief Create an identity matrix (2x2).
 * @return The identity matrix.
 */
t_matrix2d	matrix2d_identity(void);

/**
 * @brief Multiply two 2D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The product of the two matrices.
 */
t_matrix2d	matrix2d_multiply(t_matrix2d m1, t_matrix2d m2);

/**
 * @brief Multiply a 2D matrix by a scalar.
 * @param mat The matrix.
 * @param scalar The scalar value.
 * @return The scaled matrix.
 */
t_matrix2d	matrix2d_scalar_multiply(t_matrix2d mat, MYFLOAT scalar);

/**
 * @brief Add two 2D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The sum of the two matrices.
 */
t_matrix2d	matrix2d_add(t_matrix2d m1, t_matrix2d m2);

/**
 * @brief Subtract one 2D matrix from another.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The result of the subtraction.
 */
t_matrix2d	matrix2d_sub(t_matrix2d m1, t_matrix2d m2);

/**
 * @brief Transpose a 2D matrix.
 * @param mat The matrix.
 * @return The transposed matrix.
 */
t_matrix2d	matrix2d_transpose(t_matrix2d mat);

/**
 * @brief Determinant of a 2D matrix.
 * @param mat The matrix.
 * @return The determinant of the matrix.
 */
MYFLOAT	matrix2d_determinant(t_matrix2d mat);

/**
 * @brief Inverse of a 2D matrix.
 * @param mat The matrix.
 * @return The inverse matrix, if it exists. Otherwise, returns a zero matrix.
 */
t_matrix2d	matrix2d_inverse(t_matrix2d mat);

/**
 * @brief Apply a 2D matrix transformation to a 2D vector.
 * @param mat The matrix.
 * @param vec The vector.
 * @return The transformed vector.
 */
t_vec2	matrix2d_transform(t_matrix2d mat, t_vec2 vec);




#endif // MATRIX2D_H