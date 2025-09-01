/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:33:20 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 12:12:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_string.h"
# include "ft_conv.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

/**
 * @brief Main metadata struct for the get next line data
 * 
 */
typedef struct s_gnlbuffer
{
	/// @brief Exit buffer to store leftover data
	char	*exit;
	/// @brief Swap pointer
	char	*swap;
	/// @brief EOF was reached
	int		eof;
	/// @brief The master buffer used to read
	char	*buff;
}	t_gnlbuffer;

/**
 * @brief Get the next line 
 * 
 * @param fd filedescriptor to read from
 * @return char* an allocated line read from fd
 * @warning - Heap allocation must be free'd
 * @warning - Memory can leak if file descriptor is not read to the end
 */
char	*get_next_line(int fd);

/**
 * @brief String join that can also free data passed in
 * 
 * Poor form, really poor form.
 * 
 * @param s1 String 1
 * @param s2 String 2
 * @param flag Flag to free either 1, 2 or both
 * @return char* allocated string of joined strings
 * @warning Input's can be freed inside this function
 * @warning Heap allocation must be free'd
 */
char	*fancy_str_join( char *s1, char *s2, int flag);

/**
 * @brief Bzero but it returns the pointer for function chaining
 * 
 * @param ptr Pointer to data to zero out
 * @param size Bytes to zero out
 * @return void* same pointer as ptr
 */
void	*zeroit(void *ptr, size_t size);

#endif
