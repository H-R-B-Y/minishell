/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:16:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/08 10:56:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_H
# define DEFINED_H

#include <stdint.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/*
The reason this is here is to allow for easy switching between float types,
double types, and long double types for the entire project. This is useful for
performance tuning and precision requirements.
*/
#ifndef MYFLOAT
# define MYFLOAT float
#endif

# ifndef FREE_TYPEDEF
#  define FREE_TYPEDEF
typedef void				(*t_freefn)(void *);
# endif

typedef MYFLOAT				t_float;

typedef uint8_t				t_u8;
typedef uint16_t			t_u16;
typedef uint32_t			t_u32;
typedef uint64_t			t_u64;

typedef int8_t				t_s8;
typedef int16_t				t_s16;
typedef int32_t				t_s32;
typedef int64_t				t_s64;

typedef volatile t_u8		t_vu8;
typedef volatile t_u16		t_vu16;
typedef volatile t_u32		t_vu32;
typedef volatile t_u64		t_vu64;

typedef volatile t_s8		t_vs8;
typedef volatile t_s16		t_vs16;
typedef volatile t_s32		t_vs32;
typedef volatile t_s64		t_vs64;

typedef enum e_returncode	t_returncode;
enum e_returncode
{
	/// @brief Successful execution
	RETURN_OK,
	/// @brief Non-fatal error occurred
	RETURN_ERROR,
	/// @brief Fatal error occurred (suggest abort)
	RETURN_FATAL,
	/// @brief Count of return codes (not a return code itself)
	RETURN_CODE_COUNT
};


#endif