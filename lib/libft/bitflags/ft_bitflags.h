/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitflags.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:05:02 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/09 15:16:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BITFLAGS_H
# define FT_BITFLAGS_H

#include "defined.h"

typedef t_u64	t_bitfield;

int			bit_has_flag(t_bitfield flags, t_bitfield flag);
t_bitfield	bit_set_flags(t_bitfield flags, t_bitfield to_set);
int			bit_has_some_flags(t_bitfield flags, t_bitfield to_check);
int			bit_has_all_flags(t_bitfield flags, t_bitfield to_check);
t_bitfield	bit_unset_flags(t_bitfield flags, t_bitfield to_unset);
t_bitfield	bit_toggle_flags(t_bitfield flags, t_bitfield to_toggle);

#endif