/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:17:54 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/26 10:18:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CTYPE_H
# define FT_CTYPE_H

/**
 * @brief Check if a character is a letter
 * @param c Character to check
 * @return 1 if c is a letter, 0 otherwise
 */
int				ft_isalpha(int c);

/**
 * @brief Check if a character is a digit
 * @param c Character to check
 * @return 1 if c is a digit, 0 otherwise
 */
int				ft_isdigit(int c);

/**
 * @brief Check if a character is a letter or a digit
 * @param c Character to check
 * @return 1 if c is a letter or a digit, 0 otherwise
 */
int				ft_isalnum(int c);

/**
 * @brief Check if a character is ascii
 * @param c Character to check
 * @return 1 if c is ascii, 0 otherwise
 */
int				ft_isascii(int c);

/**
 * @brief Check if a character is printable
 * @param c Character to check
 * @return 1 if c is printable, 0 otherwise
 */
int				ft_isprint(int c);

/**
 * @brief Check if a character is a whitespace character
 * @param c Character to check
 * @return 1 if c is a whitespace character, 0 otherwise
 */
int				ft_iswhitespace(int c);

/**
 * @brief Convert a character to uppercase
 * @param c Character to convert
 * @return c if c is not a lowercase letter OR the uppercase variant of c
 */
int				ft_toupper(int c);

/**
 * @brief Convert a character to lowercase
 * @param c Character to convert
 * @return c if c is not an uppercase letter OR the lowercase variant of c
 */
int				ft_tolower(int c);

#endif
