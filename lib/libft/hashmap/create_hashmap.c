/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_create_hashmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:31:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/20 12:34:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

t_hashmap	hm_create(t_hashfnc hashfnc, t_hashcmp hashcmp)
{
	return (
		(t_hashmap){
			.hash_cmp = hashcmp,
			.hash_key = hashfnc,
			.pairs = {0}
		}
	);
}
