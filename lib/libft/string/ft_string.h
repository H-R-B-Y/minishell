/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:26:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/01 12:06:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# include <stdlib.h>
# include <sys/types.h>
# include "ft_mem.h"

/**
 * @brief Get the length of a string.
 * @param str String to get the length of
 * @return Length of the string
 * @warning String must be null terminated
 */
size_t			ft_strlen(const char *str);

/**
 * @brief Copy a string to another string
 * @param dest Destination string
 * @param src Source string
 * @param size Size of the destination string
 * @return Length of the source string
 * @warning Strings must be null terminated
 */
size_t			ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief Concatenate a string to another string
 * @param dest Destination string
 * @param src Source string
 * @param size Size of the destination string
 * @return Length of the source string or size if the dest is truncated
 * @warning Strings must be null terminated
 */
size_t			ft_strlcat(char *dest, const char *src, size_t size);


/**
 * @brief Get first occurance of a character in a string
 * @param str String to check
 * @param c Character to check
 * @return Pointer to the first occurance of c in str or 0 if c is not in str
 * @warning String must be null terminated
 */
char			*ft_strchr(const char *str, int c);

/**
 * @brief Get the index of the first occurance of a character in a string
 * @param str String to check
 * @param c Character to check
 * @return Index the first occurance of c in str or -1 if c is not in str
 * @warning String must be null terminated
 */
size_t			ft_strchr_i(const char *s, int c);

/**
 * @brief Get last occurace of a character in a string
 * @param str String to check
 * @param c Character to check
 * @return Pointer to the last occurance of c in str or 0 if c is not in str
 * @warning String must be null terminated
 */
char			*ft_strrchr(const char *str, const int c);

/**
 * @brief compare two strings
 * 
 * @param s1 first string
 * @param s2 second string
 * @return int the integer difference between the strings (0 if same)
 */
int				ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Compare two strings up to n characters
 * @param s1 First string
 * @param s2 Second string
 * @param n Number of characters to compare
 * @return 0 if the strings are equal, a non 0 int otherwise
 * @warning Strings must be null terminated
 */
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief get the first occurance of little in big up to len characters
 * @param big String to search in
 * @param little String to search for
 * @param len Number of characters to search
 * @return Pointer to the first occurance of
 * 	little in big or 0 if little is not in big
 * @warning Strings must be null terminated
 */
char			*ft_strnstr(const char *big,
					const char *little, size_t len);

/**
 * @brief Copy a string
 * @param src String to copy
 * @return A malloc'd copy of src or 0 if malloc fails
 * @warning String must be null terminated
 */
char			*ft_strdup(const char *src);

/**
 * @brief Copy a string  - copies at most n bytes
 * @param src String to copy
 * @param n bites to copy
 * @return A malloc'd copy of src or 0 if malloc fails
 * @warning String must be null terminated
 */
char			*ft_strndup(const char *src, size_t n);

/**
 * @brief Copy a string up to len characters
 * @param src String to copy
 * @param len Number of characters to copy
 * @return A malloc'd copy of src or 0 if malloc fails
 * @warning String must be null terminated
 */
char			*ft_substr(const char *str, size_t start, size_t len);

/**
 * @brief Concatenate two strings
 * @param s1 First string
 * @param s2 Second string
 * @return A malloc'd string containing s1 and s2 or 0 if malloc fails
 * @warning Strings must be null terminated
 */
char			*ft_strjoin(const char *s1, const char *s2);

/**
 * @brief Trim a set of characters from the start and end of a string
 * @param s1 String to trim
 * @param set Set of characters to trim
 * @return A malloc'd string containing s1 with set
 * 	trimmed from the start and end
 * @warning Strings must be null terminated
 */
char			*ft_strtrim(const char*s1, const char *set);

/**
 * @brief Split a string by a character
 * @param str String to split
 * @param c Character to split by
 * @return A malloc'd array of split substrings.
 * @warning String must be null terminated
 * @warning All substrings must be free'd
 */
char			**ft_split(const char *str, char c);

/**
 * @brief Split a string by a function
 * @param str String to split
 * @param delim function used to determine if a char is a deliminator
 * @return A malloc'd array of split substrings.
 * @warning String must be null terminated
 * @warning All substrings must be free'd
 */
char			**ft_splitfn(char const *s, int (*delim)(int c));

/**
 * @brief Split but uses a function and doesn't split when quoted.
 * @param str String to split.
 * @param delim Function to use to denote deliminator.
 * @return A malloc'd array of split substrings.
 * @warning String must be null terminated.
 * @warning All substring must be free'd 
 */
char			**ft_splitquoted(const char *str, int (*delim)(int c));

/**
 * @brief Apply a function to each character of a string
 * @param s String to iterate over
 * @param f Function to apply
 * @return A malloc'd string containing the result of f applied to each character
 */
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/**
 * @brief Apply a function to each character of a string
 * @param s String to iterate over
 * @param f Function to apply
 * @return Nothing XD
 */
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief count the occurences of c in str
 * 
 * @param str string to check
 * @param c character to count
 * @return ssize_t occurences or -1
 */
ssize_t			ft_strcountchar(const char *str, char c);


/**
 * @brief Right trim characters in the set from the string s1
 * 
 * @param s1 string to trim
 * @param set set of characters to trim from the string
 * @return char* an allocated trimmed copy of s1
 * @warning Heap allocation needs to be free'd
 */
char			*ft_strrtrim(const char *s1, const char *set);

/**
 * @brief Left trim characters in the set from the string s1
 * 
 * @param s1 The string to trim
 * @param set The set of characters to trim from the string
 * @return char* an allocated trimmed copy of s1
 * @warning Heap allocation needs to be free'd
 */
char			*ft_strltrim(const char *s1, const char *set);

/**
 * @brief Combine strings from a vector into a single string.
 * 
 * @warning Heap allocated memory must be free'd
 * @warning Array must be null terminated
 * @warning Strings must be null terminated
 * 
 * @param arr Array of strings to join
 * @return char* Single string contaning the strings from the array
 */
char	*ft_strvecjoin(const char **arr);

#endif
