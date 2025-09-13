/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_has_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:11:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:11:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitflags.h"

inline int	bit_has_flag(t_bitfield flags, t_bitfield flag)
{
	return ((flags & flag) == flag);
}
