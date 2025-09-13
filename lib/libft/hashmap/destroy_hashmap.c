/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_hashmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:33:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:48:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include <stdlib.h>

void		hm_destroy_pairlist(t_hashpair **pair)
{
	t_hashpair	*p;

	if (!pair || !*pair)
		return;
	p = *pair;
	if (p->next)
		hm_destroy_pairlist(&p->next);
	free(p);
	*pair = 0;
}

int			hm_destroy(t_hashmap *hashmap)
{
	size_t	idx;

	if (!hashmap)
		return (RETURN_ERROR);
	idx = 0;
	while (idx < hashmap->max_hashes)
	{
		if (hashmap->pairs[idx])
			hm_destroy_pairlist(&hashmap->pairs[idx]);
		idx++;
	}
	free(hashmap->pairs);
	return (RETURN_OK);
}
