/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:19:26 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 11:53:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include "ft_string.h"

/**
 * @brief Write a character to a file descriptor
 * @param c Character to write
 * @param fd File descriptor to write to
 */
void			ft_putchar_fd(char c, int fd);

/**
 * @brief Write a string to a file descriptor
 * @param s String to write
 * @param fd File descriptor to write to
 */
void			ft_putstr_fd(char *s, int fd);

/**
 * @brief Write a string to a file descriptor followed by a newline
 * @param s String to write
 * @param fd File descriptor to write to
 */
void			ft_putendl_fd(char *s, int fd);

/**
 * @brief Write an integer to a file descriptor
 * @param n Integer to write
 * @param fd File descriptor to write to
 */
void			ft_putnbr_fd(int n, int fd);

// Handles the majority of printing in the string. (calls handle escape on %)
int		ft_printf(const char *str, ...);

/**
 * @brief print formatted string to the file descriptor fd
 * @param fd the fd to print the string too
 * @param str the string to format
 * @param vargs arguments to format the string with
 */
int		ft_fprintf(int fd, const char *str, ...);

/**
 * @brief Get the next line 
 * 
 * @param fd filedescriptor to read from
 * @return char* an allocated line read from fd
 * @warning - Heap allocation must be free'd
 * @warning - Memory can leak if file descriptor is not read to the end
 */
char	*get_next_line(int fd);

#endif
