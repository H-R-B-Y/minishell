/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:16:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/28 12:30:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_H
# define DEFINED_H

#include <stdint.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef MYFLOAT
# define MYFLOAT float
#endif

typedef uint8_t u8;   ///<  8-bit unsigned integer
typedef uint16_t u16; ///< 16-bit unsigned integer
typedef uint32_t u32; ///< 32-bit unsigned integer
typedef uint64_t u64; ///< 64-bit unsigned integer

typedef int8_t s8;   ///<  8-bit signed integer
typedef int16_t s16; ///< 16-bit signed integer
typedef int32_t s32; ///< 32-bit signed integer
typedef int64_t s64; ///< 64-bit signed integer

typedef volatile u8 vu8;   ///<  8-bit volatile unsigned integer.
typedef volatile u16 vu16; ///< 16-bit volatile unsigned integer.
typedef volatile u32 vu32; ///< 32-bit volatile unsigned integer.
typedef volatile u64 vu64; ///< 64-bit volatile unsigned integer.

typedef volatile s8 vs8;   ///<  8-bit volatile signed integer.
typedef volatile s16 vs16; ///< 16-bit volatile signed integer.
typedef volatile s32 vs32; ///< 32-bit volatile signed integer.
typedef volatile s64 vs64; ///< 64-bit volatile signed integer.

typedef enum e_returncode	t_returncode;
enum e_returncode
{
	RETURN_OK,
	RETURN_ERROR,
	RETURN_FATAL,
	RETURN_CODE_COUNT
};


#endif