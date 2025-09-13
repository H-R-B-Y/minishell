/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:15:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 12:09:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONV_H
# define FT_CONV_H
# include <stdlib.h>
# include "ft_ctype.h"

/**
 * @brief Convert a string to an integer
 * @param nptr String to convert
 * @return Integer representation of the string or 0
 */
int				ft_atoi(const char *nptr);

/**
 * @brief simple implementation of atof
 * @warning Experimental
 * @param str str to convert to a float
 */
float			ft_atof(const char *str);

/**
 * @brief Convert an integer to a string
 * @param n Integer to convert
 * @return A malloc'd string containing the integer or 0 if malloc fails
 */
char			*ft_itoa(int n);


/**
 * @brief Atoi but will return 0 if the provided string is not entirely
 * made of digits.
 * 
 * @param nptr String representation of the number
 * @return int Int representation of the number
 */
int				ft_atoi_unsafe(const char *nptr);

#endif