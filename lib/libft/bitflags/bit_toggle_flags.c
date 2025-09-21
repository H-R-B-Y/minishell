/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_toggle_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:12:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:12:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitflags.h"

inline t_bitfield	bit_toggle_flags(t_bitfield flags, t_bitfield to_toggle)
{
	return (flags ^ to_toggle);
}
