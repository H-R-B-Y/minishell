/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_rgba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:23:14 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:49:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_u32	colour_rgba(t_u8 red,
	t_u8 green,
	t_u8 blue,
	t_u8 alpha)
{
	t_u32	out;

	out = 0;
	out += (red << 24);
	out += (green << 16);
	out += (blue << 8);
	out += (alpha);
	return (out);
}

t_u32	lerp_colour(t_u32 from, t_u32 too, float t)
{
	t_u8	r;
	t_u8	g;
	t_u8	b;
	t_u8	a;

	r = (t_u8)lerp((float)rgba_get_red(from),
			(float)rgba_get_red(too), t);
	g = (t_u8)lerp((float)rgba_get_green(from),
			(float)rgba_get_green(too), t);
	b = (t_u8)lerp((float)rgba_get_blue(from),
			(float)rgba_get_blue(too), t);
	a = (t_u8)lerp((float)rgba_get_alph(from),
			(float)rgba_get_alph(too), t);
	return (colour_rgba(r, g, b, a));
}

t_u32	parse_rgba_str(const char *rgba)
{
	t_u32	result;
	int			i;
	char		c;

	if (rgba == 0 || rgba[0] != '0' || rgba[1] != 'x')
		return (0);
	result = 0;
	i = 2;
	while (rgba[i] != '\0')
	{
		result <<= 4;
		c = rgba[i];
		if (c >= '0' && c <= '9')
			result |= (c - '0');
		else if (c >= 'A' && c <= 'F')
			result |= (c - 'A' + 10);
		else if (c >= 'a' && c <= 'f')
			result |= (c - 'a' + 10);
		else
			return (0);
		i++;
	}
	return (result);
}
