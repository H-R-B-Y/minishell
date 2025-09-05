/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:21:04 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 12:23:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "defined.h"

# ifdef FT_INCLUDE_ALL
#  define FT_INCLUDE_ARRAY
#  define FT_INCLUDE_CONV
#  define FT_INCLUDE_CTYPE
#  define FT_INCLUDE_IO
#  define FT_INCLUDE_LIST
#  define FT_INCLUDE_MEM
#  define FT_INCLUDE_RAND
#  define FT_INCLUDE_STRING
#  define FT_INCLUDE_CDLL
#  define FT_INCLUDE_MATH
#  define FT_INCLUDE_HASHMAP
# define FT_INCLUDE_SPMC_RINGBUFF
# endif

# ifdef FT_INCLUDE_CORE
#  define FT_INCLUDE_CONV
#  define FT_INCLUDE_CTYPE
#  define FT_INCLUDE_IO
#  define FT_INCLUDE_LIST
#  define FT_INCLUDE_MEM
#  define FT_INCLUDE_STRING
# endif

# ifdef FT_INCLUDE_ARRAY
#  include "ft_arr.h"
# endif

# ifdef FT_INCLUDE_CONV
#  include "ft_conv.h"
# endif

# ifdef FT_INCLUDE_CTYPE
#  include "ft_ctype.h"
# endif

# ifdef FT_INCLUDE_IO
#  include "ft_io.h"
# endif

# ifdef FT_INCLUDE_LIST
#  include "ft_list.h"
# endif

# ifdef FT_INCLUDE_MEM
#  include "ft_mem.h"
# endif

# ifdef FT_INCLUDE_RAND
#  include "ft_rand.h"
# endif

# ifdef FT_INCLUDE_STRING
#  include "ft_string.h"
# endif

# ifdef FT_INCLUDE_CDLL
#  include "ft_cdll.h"
# endif

# ifdef FT_INCLUDE_MATH
#  include "matrix2d.h"
#  include "matrix3d.h"
#  include "matrix4d.h"
#  include "vec2d.h"
#  include "vec3d.h"
#  include "vec4d.h"
#  include "ft_math.h"
# endif

# ifdef FT_INCLUDE_HASHMAP
#  include "ft_hashmap.h"
# endif

# ifdef FT_INCLUDE_SPMC_RINGBUFF
#  include "ft_mpmc_ringbuff.h"
# endif

#endif
