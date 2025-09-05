/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:23:56 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:01:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEM_H
# define FT_MEM_H

# include <stdlib.h>
# include <sys/types.h>

/**
 * @brief Set n bytes of a string to 0
 * @param s String to set
 * @param n Number of bytes to set
 * @return Pointer to the string
 */
void			ft_bzero(void *s, size_t n);

/**
 * @brief Allocate memory for nmemb elements of size bytes
 * @param nmemb Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated memory or 0 if malloc fails
 */
void			*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief swap the value of a with b, free previous contents of a
 * 
 * @warning VERY DIRTY
 * 
 * @param a pointer to a value you want to swap
 * @param b the new value
 * @param del function to free the original contents of a (optional)
 * @return returns the new value stored in a
 */
void			*ft_dirtyswap(void **a, void *b, void (*del)(void *));


/**
 * @brief Set n bytes of a string to a character
 * @param str String to set
 * @param c Character to set
 * @param n Number of bytes to set
 * @return Pointer to the string
 */
void			*ft_memset(void *str, int c, size_t n);


/**
 * @brief Copy n bytes from src to dest
 * @param dest Destination string
 * @param src Source string
 * @param n Number of bytes to copy
 * @return Pointer to dest
 */
void			*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copy n bytes from src to dest
 * @param dest Destination string
 * @param src Source string
 * @param n Number of bytes to copy
 * @return Pointer to dest
 */
void			*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Get first occurance of byte c in the first n bytes of s
 * @param s String to search
 * @param c Byte to search for
 * @param n Number of bytes to search
 * @return Pointer to the first occurance of c in s or 0 if c is not in s
 */
void			*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compare two memory regions
 * @param s1 First memory region
 * @param s2 Second memory region
 * @param n Number of bytes to compare
 * @return 0 if the memory regions are equal, a non 0 int otherwise
 */
int				ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
