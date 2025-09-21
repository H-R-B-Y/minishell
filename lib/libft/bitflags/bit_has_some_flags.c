/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_has_some_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:12:00 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:12:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitflags.h"

inline int	bit_has_some_flags(t_bitfield flags, t_bitfield to_check)
{
	return ((flags & to_check) != 0);
}
