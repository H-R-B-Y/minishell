/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:25:42 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 15:05:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAND_H
# define FT_RAND_H

# ifndef RANDSEED
#  define RANDSEED 42
# endif

/*
Xorshift parameters. These can be changed to alter the characteristics of
the random number generator. The values here are commonly used.
*/
# define XOR_A 13
# define XOR_B 15
# define XOR_C 5

/**
 * @brief Set the seed for the random number generator
 *
 * @param seed The seed value to initialize the generator
 */
void			ft_srand(int seed);

/**
 * @brief Generate a random integer between min and max (inclusive)
 * 
 * The method used is the xorshift algorithm, which is a simple and fast
 * pseudo-random number generator. It is not suitable for cryptographic purposes.
 *
 * @param min The minimum value (inclusive)
 * @param max The maximum value (inclusive)
 * @return int A random integer between min and max
 */
int				ft_rand(int min, int max);

/**
 * @brief Generate a random integer between min and max (inclusive)
 * 
 * The method used is the xorshift algorithm, which is a simple and fast
 * pseudo-random number generator. It is not suitable for cryptographic purposes.
 * 
 * This function's seed is defined at compile time using the RANDSEED macro.
 * 
 * @param min The minimum value (inclusive)
 * @param max The maximum value (inclusive)
 * @return int A random integer between min and max
 */
int				ft_rand2(int min, int max);

#endif
