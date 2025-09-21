/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_get_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:55:23 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/07 14:47:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"

void		*pair_get_value(t_hashmap *hashmap,
	t_hashpair *head,
	const void *key
)
{
	register t_hashpair	*node;

	if (!hashmap || !head || !key)
		return (0);
	node = head;
	while (node)
	{
		if (hashmap->hash_cmp(key, node->key) == 0)
			return ((void *)node->value);
		node = node->next;
	}
	return (0);
}

void		*hm_get_value(t_hashmap *hashmap, const void *key)
{
	register unsigned int	hash;

	if (!hashmap || !key)
		return (0);
	hash = hashmap->hash_key(key) % hashmap->max_hashes;
	return (pair_get_value(hashmap, hashmap->pairs[hash], key));
}
