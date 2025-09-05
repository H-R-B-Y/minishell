/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:25:42 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:41:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RAND_H
# define FT_RAND_H

# ifndef RANDSEED
#  define RANDSEED 42
# endif

/**
 * @brief Creates a random number based on the seed RANDSEED
 * 
 * Note that the seed is set at compile time so all runs will have the same
 * base seed, meaning this is essentially useless.
 * 
 * @param min the minimum of the random number (inclusive)
 * @param max the maximum of the random number (inclusive)
 * @return int a new random number in the range
 */
int				ft_rand(int min, int max);

#endif
