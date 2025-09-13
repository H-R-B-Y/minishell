/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_set_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:12:11 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:12:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitflags.h"

inline t_bitfield	bit_set_flags(t_bitfield flags, t_bitfield to_set)
{
	return (flags | to_set);
}
