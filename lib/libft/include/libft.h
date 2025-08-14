/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:21:04 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 18:50:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <sys/types.h>
# include <errno.h>

// ███    ███  █████  ███    ██ ██████   █████  ████████ ███████ 
// ████  ████ ██   ██ ████   ██ ██   ██ ██   ██    ██    ██      
// ██ ████ ██ ███████ ██ ██  ██ ██   ██ ███████    ██    █████   
// ██  ██  ██ ██   ██ ██  ██ ██ ██   ██ ██   ██    ██    ██      
// ██      ██ ██   ██ ██   ████ ██████  ██   ██    ██    ███████ 

# ifndef RANDSEED
#  define RANDSEED 42
# endif

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

// Str functions

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
 * @brief Concatenate a array to another array
 * @param dest Destination array
 * @param src Source array
 * @param size Size of the destination array
 * @return Length of the source array or size if the dest is truncated
 * @warning Array must be null terminated
 */
size_t			ft_arrlcat(void **dest, void **src, size_t size);

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

// Memory functions

/**
 * @brief Set n bytes of a string to a character
 * @param str String to set
 * @param c Character to set
 * @param n Number of bytes to set
 * @return Pointer to the string
 */
void			*ft_memset(void *str, int c, size_t n);

/**
 * @brief Set n bytes of a string to 0
 * @param s String to set
 * @param n Number of bytes to set
 * @return Pointer to the string
 */
void			ft_bzero(void *s, size_t n);

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

/**
 * @brief Allocate memory for nmemb elements of size bytes
 * @param nmemb Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated memory or 0 if malloc fails
 */
void			*ft_calloc(size_t nmemb, size_t size);

// Ascii <-> Int functions

/**
 * @brief Convert a string to an integer
 * @param nptr String to convert
 * @return Integer representation of the string or 0
 */
int				ft_atoi(const char *nptr);

/**
 * @brief Convert an integer to a string
 * @param n Integer to convert
 * @return A malloc'd string containing the integer or 0 if malloc fails
 */
char			*ft_itoa(int n);

// Iteration

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

// IO

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

// ██████   ██████  ███    ██ ██    ██ ███████ 
// ██   ██ ██    ██ ████   ██ ██    ██ ██      
// ██████  ██    ██ ██ ██  ██ ██    ██ ███████ 
// ██   ██ ██    ██ ██  ██ ██ ██    ██      ██ 
// ██████   ██████  ██   ████  ██████  ███████ 

/**
 * @brief Linked list
 * @param content Pointer to the content of the list item
 * @param next Pointer to the next list item or 0
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Creation

/**
 * @brief Create a new list item
 * @param content Pointer to the content of the list item
 * @return Pointer to the new list item or 0 if malloc fails
 */
t_list			*ft_lstnew(void *content);

/**
 * @brief Add a new list item to the front of a list
 * @param lst Pointer to the list
 * @param new Pointer to the new list item
 */
void			ft_lstadd_front(t_list **lst, t_list *new_node);

/**
 * @brief Add a new list item to the back of a list
 * @param lst Pointer to the list
 * @param new Pointer to the new list item
 */
void			ft_lstadd_back(t_list **lst, t_list *new_node);

// Naviation

/**
 * @brief Get the length of a list
 * @param lst Pointer to the list
 */
int				ft_lstsize(t_list *lst);

/**
 * @brief Get the last list item
 * @param lst Pointer to the list
 * @return Pointer to the last list item
 */
t_list			*ft_lstlast(t_list *lst);

/**
 * @brief Pop a node from the list lst
 * 
 * @param lst Pointer to the head of the list to pop from 
 * @return t_list* node popped from the list
 */
t_list			*ft_lstpop_back(t_list **lst);

/**
 * @brief Pop a node from the front of a list
 * 
 * The head of the list will be incremented to the next value
 * 
 * @param lst Pointer to the head of the list to pop from 
 * @return t_list* The node popped from the list
 */
t_list			*ft_lstpop_front(t_list **lst);

// Deletion

/**
 * @brief Delete a list item
 * @param lst Pointer to the list item
 * @param del Function to delete the content of the list item
 */
void			ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Delete all list items
 * @param lst Pointer to the list
 */
void			ft_lstclear(t_list **lst, void (*del)(void*));

// Iteration

/**
 * @brief Iterate over a list applying a function to each list item
 * @param lst Pointer to the list
 * @param f Function to apply to the content of each list item
 */
void			ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterate over a list applying a function to each list item
 * @param lst Pointer to the list
 * @param f Function to apply to the content of each list item
 * @return A new list containing the result of f applied to each list item
 */
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

/**
 * @brief Get a list item by index
 * @param lst Pointer to the list
 * @param index Index of the list item
 * @return Pointer to the list item or 0 if the index is out of bounds
 */
t_list			*ft_lstget(t_list *lst, size_t index);

/**
 * @brief Convert a linked list into an array
 * 
 * @param lst The list to convert to an array
 * @return void** allocated array of values from the list
 * @warning Heap allocation of the array pointer
 */
void			**ft_lstarr(t_list *lst);

/**
 * @brief Function to iterate over a list with a parameter
 * @param lst Pointer to the list
 * @param f Function to apply to the content of each list item
 * @param param Parameter to pass to the function
 */
void			ft_lstiter_param(t_list *lst,
					void (*f)(void *, void *),
					void *param);

// Experimental
/**
 * @brief simple implementation of atof
 * @param str str to convert to a float
 */
float			ft_atof(const char *str);

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
 * @brief ft_arrclear using free by default. 
 * free all items in an array using free() (including the array ptr)
 * @param chunks the array of pointers to free
 * @warning chunks must be an array of heap allocated pointers
 */
void			ft_arrfree(void **chunks);

/**
 * @brief convert an array to a list of items
 * @param chunks the array to convert
 * @warning if allocation fails the list will be free'd but not the array
 */
t_list			*ft_arrlist(void **chunks);

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

/**
 * @brief join the contents of two arrays
 * 
 * @param arr1 array one
 * @param arr2 array two
 * @return void** the new allocated array with the contents of both arrays
 */
void			**ft_arrjoin(void **arr1, void **arr2);

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
 * @brief count the occurences of c in str
 * 
 * @param str string to check
 * @param c character to count
 * @return ssize_t occurences or -1
 */
ssize_t			ft_strcountchar(const char *str, char c);

/**
 * @brief Creates a random number based on the seed RANDSEED
 * 
 * Note that the seed is set at compile time so all runs will have the same
 * base seed, meaning this is essentially useless.
 * 
 * @param min the minimum of the random number (inclusive)
 * @param max the maximum of the random number (inclusive)
 * @return int a new random number in the range
 */
int				ft_rand(int min, int max);

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

#endif
