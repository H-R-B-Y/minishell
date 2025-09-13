/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:23 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 11:33:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_conv.h"

float	ft_atof(const char *str)
{
	double	output;
	double	flt;
	int		sign;

	if (!str)
		return (0.0f);
	output = 0;
	while (*str && ft_iswhitespace(*str))
		str++;
	sign = 1;
	if (*str && *str == '-' && str++)
		sign *= -1;
	while (*str != '\0' && *str != '.' && ft_isdigit(*str))
	{
		output *= 10;
		output += *str - '0';
		str++;
	}
	if (*str == '\0' || *str != '.')
		return (output * sign);
	str++;
	flt = ft_atof(str);
	while (*str != '\0' && ft_isdigit(*str) && str++)
		flt /= 10;
	return ((output + flt) * sign);
}
