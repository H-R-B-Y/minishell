/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:12:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:52:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARR_H
# define FT_ARR_H
# include "ft_mem.h"
# include "ft_list.h"
# include "ft_string.h"
# include <sys/types.h>

/**
 * @brief Concatenate a array to another array
 * @param dest Destination array
 * @param src Source array
 * @param size Size of the destination array
 * @return Length of the source array or size if the dest is truncated
 * @warning Array must be null terminated
 */
size_t			ft_arrlcat(void **dest, void **src, size_t size);

/**
 * @brief iterates over the pointer addresses until it reaches NULL
 * @param chunks the array to iterate over
 * @warning chunks MUST BE NULL TERMINATED
 */
size_t			ft_arrlen(void **chunks);

/**
 * @brief free all items in an array (including the array ptr)
 * @param chunks the array of pointers to free
 * @param f the free function for the array items
 * @warning chunks must be an array of heap allocated pointers
 */
void			ft_arrclear(void **chunks, void (*f)(void *));

/**
 * @brief join the contents of two arrays
 * 
 * @param arr1 array one
 * @param arr2 array two
 * @return void** the new allocated array with the contents of both arrays
 */
void			**ft_arrjoin(void **arr1, void **arr2);

/**
 * @brief free all items in an array (including the array ptr)
 * @param chunks the array of pointers to free
 * @param f the free function for the array items
 * @warning chunks must be an array of heap allocated pointers
 */
void			ft_arrclear(void **chunks, void (*f)(void *));

/**
 * @brief ft_arrclear using free by default. 
 * free all items in an array using free() (including the array ptr)
 * @param chunks the array of pointers to free
 * @warning chunks must be an array of heap allocated pointers
 */
void			ft_arrfree(void **chunks);

/**
 * @brief produces malloc'd array of the result of f
 * @param arr array to iterate over
 * @param f function to perform
 * @param del delete function used when allocation f produces a null pointer
 */
void			**ft_arrmap(void **arr, void *(*f)(void *),
					void (*del)(void *));

/**
 * @brief iterate through an array applying the function to each item
 * 
 * @param arr the array to iterate over
 * @param f the function to apply to each item
 */
void			ft_arriter(void **arr, void *(*f)(void *));

/**
 * @brief add a new item to the end of an array or create a new one
 * 
 * @param arr the array to add too
 * @param newitem the new item to add
 * @return void** new allocated array containing the newitem
 */
void			**ft_arradd_back(void **arr, void *newitem);

/**
 * @brief add a new item to the front of an array
 * 
 * @param arr the array to add too
 * @param newitem the new item to add
 * @return void** new allocated array containing the newitem
 */
void			**ft_arradd_front(void **arr, void *newitem);

/**
 * @brief add a new item to the array at a given index
 * 
 * @param arr the array to add too
 * @param newitem the new item to add 
 * @param index the index to insert at
 * @return void** new allocated array containing the newitem
 */
void			**ft_arradd_atindex(void **arr, void *newitem, size_t index);

/**
 * @brief delete an item in an array at a given index
 * 
 * @param arr the array to delete from
 * @param index the index in the array we are deleting from
 * @param del function to delete item in arr (optional)
 * @return void** a new allocated array with the item at index removed
 */
void			**ft_arrdel_atindex(void **arr,
					size_t index, void (*del)(void *));

# ifdef FT_ENABLE_LIST
#  include "../linked_list/ft_list.h"

/**
 * @brief convert an array to a list of items
 * @param chunks the array to convert
 * @warning if allocation fails the list will be free'd but not the array
 */
t_list			*ft_arrlist(void **chunks);

# endif

#endif