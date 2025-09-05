/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_rgba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:23:14 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:07:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

u32	colour_rgba(u8 red,
	u8 green,
	u8 blue,
	u8 alpha)
{
	u32	out;

	out = 0;
	out += (red << 24);
	out += (green << 16);
	out += (blue << 8);
	out += (alpha);
	return (out);
}

u32	lerp_colour(u32 from, u32 too, float t)
{
	u8	r;
	u8	g;
	u8	b;
	u8	a;

	r = (u8)lerp((float)rgba_get_red(from),
			(float)rgba_get_red(too), t);
	g = (u8)lerp((float)rgba_get_green(from),
			(float)rgba_get_green(too), t);
	b = (u8)lerp((float)rgba_get_blue(from),
			(float)rgba_get_blue(too), t);
	a = (u8)lerp((float)rgba_get_alph(from),
			(float)rgba_get_alph(too), t);
	return (colour_rgba(r, g, b, a));
}

u32	parse_rgba_str(const char *rgba)
{
	u32	result;
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
