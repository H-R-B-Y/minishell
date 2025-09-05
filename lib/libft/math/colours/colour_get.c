/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:14:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 10:07:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

u8	rgba_get_red(u32 colour)
{
	return ((colour & 0xFF000000) >> 24);
}

u8	rgba_get_green(u32 colour)
{
	return ((colour & 0x00FF0000) >> 16);
}

u8	rgba_get_blue(u32 colour)
{
	return ((colour & 0x0000FF00) >> 8);
}

u8	rgba_get_alph(u32 colour)
{
	return (colour & 0x000000FF);
}
