/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:11:38 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/27 11:47:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HB_MATH_EXT_H
# define HB_MATH_EXT_H

# include <math.h>

# include "matrix4d.h"
# include "matrix3d.h"
# include "matrix2d.h"
# include "vec2d.h"
# include "vec3d.h"
# include "vec4d.h"

// ███    ███ ██ ███████  ██████ 
// ████  ████ ██ ██      ██      
// ██ ████ ██ ██ ███████ ██      
// ██  ██  ██ ██      ██ ██      
// ██      ██ ██ ███████  ██████ 

MYFLOAT		lerp(MYFLOAT start, MYFLOAT end, MYFLOAT t);

MYFLOAT		normalize(MYFLOAT from, MYFLOAT too, float t);

// Note: x is start, y is end.
MYFLOAT		maprange(t_vec2 from, t_vec2 too, MYFLOAT t);

//  ██████  ██████  ██       ██████  ██    ██ ██████  
// ██      ██    ██ ██      ██    ██ ██    ██ ██   ██ 
// ██      ██    ██ ██      ██    ██ ██    ██ ██████  
// ██      ██    ██ ██      ██    ██ ██    ██ ██   ██ 
//  ██████  ██████  ███████  ██████   ██████  ██   ██ 

u8	rgba_get_red(u32 colour);
u8	rgba_get_green(u32 colour);
u8	rgba_get_blue(u32 colour);
u8	rgba_get_alph(u32 colour);

u32	colour_rgba(u8 red,
				u8 green,
				u8 blue,
				u8 alpha);

u32	lerp_colour(u32 from, u32 too, float t);

u32	parse_rgba_str(const char *rgba);

#endif