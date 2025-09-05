#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "defined.h"
#include "vec3d.h"  // Assuming you have vec3d operations in this header.

typedef union s_matrix3d
{
	struct
	{
		t_vec3 x;  // First row (x values)
		t_vec3 y;  // Second row (y values)
		t_vec3 z;  // Third row (z values)
	};
	struct
	{
		MYFLOAT x1, y1, z1;  // First row elements
		MYFLOAT x2, y2, z2;  // Second row elements
		MYFLOAT x3, y3, z3;  // Third row elements
	};
	MYFLOAT m[3][3];  // 3D array representation
} __attribute__((aligned(8)))	t_matrix3d;

// Function declarations

/**
 * @brief Create an identity matrix (3x3).
 * @return The identity matrix.
 */
t_matrix3d	matrix3d_identity(void);

/**
 * @brief Multiply two 3D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The product of the two matrices.
 */
t_matrix3d	matrix3d_multiply(t_matrix3d m1, t_matrix3d m2);

/**
 * @brief Multiply a 3D matrix by a scalar.
 * @param mat The matrix.
 * @param scalar The scalar value.
 * @return The scaled matrix.
 */
t_matrix3d	matrix3d_scalar_multiply(t_matrix3d mat, MYFLOAT scalar);

/**
 * @brief Add two 3D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The sum of the two matrices.
 */
t_matrix3d	matrix3d_add(t_matrix3d m1, t_matrix3d m2);

/**
 * @brief Subtract one 3D matrix from another.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The result of the subtraction.
 */
t_matrix3d	matrix3d_sub(t_matrix3d m1, t_matrix3d m2);

/**
 * @brief Transpose a 3D matrix.
 * @param mat The matrix.
 * @return The transposed matrix.
 */
t_matrix3d	matrix3d_transpose(t_matrix3d mat);

/**
 * @brief Determinant of a 3D matrix.
 * @param mat The matrix.
 * @return The determinant of the matrix.
 */
MYFLOAT	matrix3d_determinant(t_matrix3d mat);

/**
 * @brief Inverse of a 3D matrix.
 * @param mat The matrix.
 * @return The inverse matrix, if it exists. Otherwise, returns a zero matrix.
 */
t_matrix3d	matrix3d_inverse(t_matrix3d mat);

/**
 * @brief Apply a 3D matrix transformation to a 3D vector.
 * @param mat The matrix.
 * @param vec The vector.
 * @return The transformed vector.
 */
t_vec3	matrix3d_transform(t_matrix3d mat, t_vec3 vec);


#endif // MATRIX3D_H
