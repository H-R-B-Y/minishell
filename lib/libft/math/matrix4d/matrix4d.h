#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "defined.h"
#include "vec4d.h" // Include your 4D vector header here
#include "vec3d.h"

// Matrix 4D struct definition
typedef union s_matrix4d {

	struct {
		t_vec4 x;  // First row
		t_vec4 y;  // Second row
		t_vec4 z;  // Third row
		t_vec4 w;  // Fourth row
	};
	struct {
		MYFLOAT x1, y1, z1, w1;  // First row elements
		MYFLOAT x2, y2, z2, w2;  // Second row elements
		MYFLOAT x3, y3, z3, w3;  // Third row elements
		MYFLOAT x4, y4, z4, w4;  // Fourth row elements
	};
	MYFLOAT m[4][4];  // 4D array representation
} __attribute__((aligned(8)))	t_matrix4d;

/**
 * @brief Identity matrix for 4D space.
 * @return A 4D identity matrix (1s on the diagonal, 0s elsewhere).
 */
t_matrix4d	matrix4d_identity(void);

/**
 * @brief Multiply two 4D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The resulting matrix after multiplication.
 */
t_matrix4d	matrix4d_multiply(t_matrix4d m1, t_matrix4d m2);

/**
 * @brief Multiply a 4D matrix by a scalar.
 * @param m The matrix.
 * @param scalar The scalar value.
 * @return The scaled matrix.
 */
t_matrix4d	matrix4d_scalar_multiply(t_matrix4d m, MYFLOAT scalar);

/**
 * @brief Transpose a 4D matrix.
 * @param m The matrix.
 * @return The transposed matrix.
 */
t_matrix4d	matrix4d_transpose(t_matrix4d m);

/**
 * @brief Calculate the determinant of a 4D matrix.
 * @param m The matrix.
 * @return The determinant of the matrix.
 */
MYFLOAT	matrix4d_determinant(t_matrix4d m);

/**
 * @brief Calculate the inverse of a 4D matrix.
 * @param m The matrix.
 * @return The inverse of the matrix, or an identity matrix if it's not invertible.
 */
t_matrix4d	matrix4d_inverse(t_matrix4d m);

/**
 * @brief Create a translation matrix for 4D space.
 * @param x Translation along the x-axis.
 * @param y Translation along the y-axis.
 * @param z Translation along the z-axis.
 * @param w Translation along the w-axis.
 * @return A 4D translation matrix.
 */
t_matrix4d	matrix4d_translation(MYFLOAT x, MYFLOAT y, MYFLOAT z, MYFLOAT w);

/**
 * @brief Create a scaling matrix for 4D space.
 * @param x Scaling factor along the x-axis.
 * @param y Scaling factor along the y-axis.
 * @param z Scaling factor along the z-axis.
 * @param w Scaling factor along the w-axis.
 * @return A 4D scaling matrix.
 */
t_matrix4d	matrix4d_scaling(MYFLOAT x, MYFLOAT y, MYFLOAT z, MYFLOAT w);

/**
 * @brief Create a rotation matrix for rotating around the x-axis in 4D space.
 * @param angle The rotation angle in radians.
 * @return A 4D rotation matrix for rotating around the x-axis.
 */
t_matrix4d	matrix4d_rotate_x(MYFLOAT angle);

/**
 * @brief Create a rotation matrix for rotating around the y-axis in 4D space.
 * @param angle The rotation angle in radians.
 * @return A 4D rotation matrix for rotating around the y-axis.
 */
t_matrix4d	matrix4d_rotate_y(MYFLOAT angle);

/**
 * @brief Create a rotation matrix for rotating around the z-axis in 4D space.
 * @param angle The rotation angle in radians.
 * @return A 4D rotation matrix for rotating around the z-axis.
 */
t_matrix4d	matrix4d_rotate_z(MYFLOAT angle);

/**
 * @brief Apply a 4D matrix transformation to a 4D vector.
 * @param m The matrix.
 * @param v The 4D vector.
 * @return The transformed 4D vector.
 */
t_vec4	matrix4d_transform(t_matrix4d m, t_vec4 v);

/**
 * @brief Add two 4D matrices.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The resulting matrix after addition.
 */
t_matrix4d	matrix4d_add(t_matrix4d m1, t_matrix4d m2);

/**
 * @brief Subtract one 4D matrix from another.
 * @param m1 The first matrix.
 * @param m2 The second matrix.
 * @return The resulting matrix after subtraction.
 */
t_matrix4d	matrix4d_sub(t_matrix4d m1, t_matrix4d m2);


t_matrix4d	matrix4d_rotate(MYFLOAT x_angle, MYFLOAT y_angle, MYFLOAT z_angle);

/**
 * @brief Helper functions for matrix4d_inverse
 */
MYFLOAT	det3x3(MYFLOAT a11, MYFLOAT a12, MYFLOAT a13,
			MYFLOAT a21, MYFLOAT a22, MYFLOAT a23,
			MYFLOAT a31, MYFLOAT a32, MYFLOAT a33);
void	matrix4d_cofactor_row0(t_matrix4d matrix, t_vec4 *row, MYFLOAT det);
void	matrix4d_cofactor_row1(t_matrix4d matrix, t_vec4 *row, MYFLOAT det);
void	matrix4d_cofactor_row2(t_matrix4d matrix, t_vec4 *row, MYFLOAT det);
void	matrix4d_cofactor_row3(t_matrix4d matrix, t_vec4 *row, MYFLOAT det);

#endif // MATRIX4D_H
