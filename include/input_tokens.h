/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 19:09:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TOKENS_H
# define INPUT_TOKENS_H

#include "libft.h"

/**
 * @brief token types for tokens parsed from arguments
 * @param TOKEN_NONE token none, if this token is returned there was an error
 * @param WORD default type for string that is not a special token
 * @param PIPE token for '|'
 * @param REDIRECT_OUT token for '>'
 * @param REDIRECT_APPEND token for '>>'
 * @param REDIRECT_IN token for '<'
 * @param HEREDOC token for '<<'
 * @param AFTER token for ';'
 * @param AND_IF token for '$$'
 * @param OR_IF token for '||'
 * @param LPAREN token for '('
 * @param RPAREN token for ')'
 * @param AMP token for '&'
 * @param END_TOKEN token for end of the input line
 * @param TOKEN_COUNT count of number of valid token types
 */
typedef enum e_tokentype	t_tokentype;
enum e_tokentype
{
	TOKEN_NONE,
	WORD,
	PIPE,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_IN,
	HEREDOC,
	AFTER,
	AND_IF,
	OR_IF,
	LPAREN,
	RPAREN,
	AMP,
	END_TOKEN,
	TOKEN_COUNT
};

/**
 * @brief Get the token type of a token
 * @param raw_token the raw token string to check
 * @returns the token type for the raw token
 */
t_tokentype	bin_token(const char *raw_token);

/**
 * @brief Creates a new list node from a raw token
 * @param raw_token the raw token string
 * @returns a list node containing a new token
 * 
 * The contents of the new node will be a token struct ptr
 * the token struct will contain the raw token data as well as
 * the token type.
 */
t_list		*bin_and_create_token(char *raw_token);

/*
Debugging token type:
*/

/**
 * @brief return a string representing the token type
 * @param type the token type to get
 * @returns string representation of the token type
 */
const char	*token_type_to_string(t_tokentype type);

/**
 * @brief print the tokens type
 * @note does not print a new line
 */
void	print_token_type(t_tokentype type);

/**
 * @brief token type struct, provides information about a token
 * @param type the token type
 * @param raw the raw token string
 * @param variables_expanded flag for if the variables in the word have
 * been expanded (Might remove)
 * @param heredoc_deliminator flag for if this string is the heredoc end
 * of line deliminator (Might remove)
 * 
 */
typedef struct s_token	t_token;
struct s_token
{
	t_tokentype	type;
	char		*raw;
	char		*text;
	int			variables_expanded;
	int			heredoc_deliminator;
};

/**
 * @brief create a new token with token type and string
 * @param type the type of the token to create
 * @param raw_token the raw string of the token
 * @returns head allocated token struct
 */
t_token	*create_token(t_tokentype type, char *raw_token);

/**
 * @brief destroy a token (and optionally its contents)
 * @param token a pointer to a pointer to a token
 * @param del_raw (optional) function pointer to free the raw token
 * 
 * The value of the ptrptr will be set to null, the token will be free'd
 * if the del_raw pointer is not null it will be called on the raw token data
 */
void	destroy_token(t_token *token, void (*del_raw)(void *));

/**
 * @brief prints the token type and the tokens raw data in columns
 * @param token the token to print
 */
void	print_token(t_token *token, int column_width);


/*
Other functions
*/
/**
 * @brief returns true if the character is an operator
 * @param c the character to check
 * 
 * note that the operators are: < > ; & | ( )
 */
int		isoperator(char c);

/*
Main function that we care about
*/

t_list *tokenise(char *str);


int	cleanse_validate_tokens(t_list *tokens);

#endif
