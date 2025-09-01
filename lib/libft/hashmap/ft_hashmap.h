/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:06:09 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/28 13:09:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include <sys/types.h>

# ifndef MAXHASH
#  define MAXHASH 1024
# endif

# include "defined.h"
# include "ft_mem.h"
# define CALLOC ft_calloc

typedef unsigned int (*t_hashfnc)(const void *);
typedef int (*t_hashcmp)(const void *, const void *);
typedef struct s_hashmap	t_hashmap;
typedef struct s_hashpair	t_hashpair;

struct s_hashpair
{
	/// @brief The lookup key
	const void			*key;
	/// @brief The value of the pair
	const void			*value;
	/// @brief The next item in the pair list
	struct s_hashpair	*next;
};

/**
 * @brief Add or Update a pair in a pair list
 * 
 * @note should only be called from source
 * 
 * @param hashmap The hashmap object
 * @param head The head of the pair list
 * @param key The key to update
 * @param value The value to set
 * @return int non 0 if error
 */
int		hm_add_pair(t_hashmap *hashmap,
			t_hashpair *head,
			void *key,
			void *value);

/**
 * @brief Recursivly destroy a pair list setting pointer to pair to NULL
 * 
 * @note should only be called from source
 * 
 * @param pair Pointer to a Pointer to a pair
 */
void	hm_destroy_pairlist(t_hashpair **pair);

struct s_hashmap
{
	/// @brief Array of pair lists
	t_hashpair		*pairs[MAXHASH];
	/// @brief Function to hash keys
	t_hashfnc		hash_key;
	/// @brief Function to compare key hashes
	t_hashcmp		hash_cmp;
};

/**
 * @brief Create new hashmap object
 * 
 * @param hashfnc hashing function
 * @param hashcmp hash comparison funciton
 * @return t_hashmap new object with initial values set
 */
t_hashmap	hm_create(t_hashfnc hashfnc, t_hashcmp hashcmp);

/**
 * @brief Destroy a hashmap object
 * 
 * @param hashmap the hashmap to destroy
 * @return int not 0 on error
 */
int			hm_destroy(t_hashmap *hashmap);

/**
 * @brief Add a new value to a hashmap
 * 
 * @param hashmap The hashmap to add the value too
 * @param key The key of the pair
 * @param value The value of the pair
 * @return int non 0 on error
 */
int			hm_add_value(t_hashmap *hashmap,
				void *key, void *value);

/**
 * @brief Lookup a value in the hasmap using a key
 * 
 * @param hashmap The hashmap object
 * @param key The key to lookup
 * @return void* Value on successful lookup else NULL
 */
void		*hm_get_value(t_hashmap *hashmap, const void *key);

/*
TODO:

Funcitons for removing pairs/keys from the hashmap

Generic functions for iterating / adding / removing pairs

An overflow to add a raw pair object

I am thinking maybe hardcoding the max hashes is probably not the best idea,
I just wanted to make it so the array could be stack allocated instead
of heap allocated, maybe this should be changed in the future.
*/

#endif