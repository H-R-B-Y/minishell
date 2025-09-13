/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_unset_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:12:38 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:12:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitflags.h"

inline t_bitfield	bit_unset_flags(t_bitfield flags, t_bitfield to_unset)
{
	return (flags & ~to_unset);
}
