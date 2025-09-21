/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:14:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:49:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_u8	rgba_get_red(t_u32 colour)
{
	return ((colour & 0xFF000000) >> 24);
}

t_u8	rgba_get_green(t_u32 colour)
{
	return ((colour & 0x00FF0000) >> 16);
}

t_u8	rgba_get_blue(t_u32 colour)
{
	return ((colour & 0x0000FF00) >> 8);
}

t_u8	rgba_get_alph(t_u32 colour)
{
	return (colour & 0x000000FF);
}
