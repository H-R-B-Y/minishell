/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokens.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 09:35:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TOKENS_H
# define INPUT_TOKENS_H

# include "libft.h"

// hbreeze:
// NOTE: The order of this enum should be :
// 		NONE , Fixable errors, unfixable errors, error count

/**
 * @brief enum for the errors that might occur
 * @param TOK_ERR_NONE Error for 
 * @param UNCLOSED_SINGLEQUOTE
 * @param UNCLOSED_DOUBLEQUOTE
 * @param UNCLOSED_PARENTHESIS
 * @param OPEN_CONDITION_AND
 * @param OPEN_CONDITION_OR
 * @param UNFINISHED_PIPE
 * @param HEREDOC_WITHOUT_WORD
 * @param TOKEN_ERROR_COUNT
 */
typedef enum e_tokerr	t_tokerr;
enum e_tokerr
{
	TOK_ERR_NONE, // Nonetype
	UNCLOSED_SINGLEQUOTE, // Fixable
	UNCLOSED_DOUBLEQUOTE, // Fixable
	UNCLOSED_PARENTHESIS, // Fixable
	OPEN_CONDITION_AND, // Fixable
	OPEN_CONDITION_OR, // Fixable
	UNFINISHED_PIPE, // Fixable
	HEREDOC_WITHOUT_WORD,
	TOKEN_ERROR_COUNT // Count of errors
};

/**
 * @brief token types for tokens parsed from arguments
 * @param TOK_NONE token none, if this token is returned there was an error
 * @param TOK_WORD default type for string that is not a special token
 * @param TOK_PIPE token for '|'
 * @param TOK_REDIR_OUT token for '>'
 * @param TOK_REDIR_APPEND token for '>>'
 * @param TOK_REDIR_IN token for '<'
 * @param TOK_HEREDOC token for '<<'
 * @param TOK_AFTER token for ';'
 * @param TOK_AND_IF token for '$$'
 * @param TOK_OR_IF token for '||'
 * @param TOK_LPAREN token for '('
 * @param TOK_RPAREN token for ')'
 * @param TOK_AMP token for '&'
 * @param TOK_END token for end of the input line
 * @param TOK_COUNT count of number of valid token types
 */
typedef enum e_tokentype	t_tokentype;
enum e_tokentype
{
	TOK_NONE,
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_REDIR_IN,
	TOK_HEREDOC,
	TOK_AFTER,
	TOK_AND_IF,
	TOK_OR_IF,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_AMP,
	TOK_END,
	TOK_COUNT
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
void		print_token_type(t_tokentype type);

/**
 * @brief token type struct, provides information about a token
 * @param type the token type
 * @param raw the raw token string
 * @param variables_expanded flag for if the variables in the word have
 * been expanded (Might remove)
 * @param heredoc_deliminator flag for if this string is the heredoc end
 * of line deliminator (Might remove)
 */
typedef struct s_token		t_token;
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
t_token		*create_token(t_tokentype type, char *raw_token);

/**
 * @brief destroy a token (and optionally its contents)
 * @param token a pointer to a pointer to a token
 * @param del_raw (optional) function pointer to free the raw token
 * @param del_str (optional) funciton pointer to free the str of the token
 * 
 * The value of the ptrptr will be set to null, the token will be free'd
 * if the del_raw pointer is not null it will be called on the raw token data
 */
void	destroy_token(t_token *token, void (*del_raw)(void *), void (*del_str)(void *));


/**
 * @brief prints the token type and the tokens raw data in columns
 * @param token the token to print
 */
void		print_token(t_token *token, int column_width);


void	free_token_list(t_list *list, void (*del_raw)(void *), void (*del_str)(void *));
void	free_token_vector(t_token **vec, void (*del_raw)(void *), void (*del_str)(void *));

/*
Other functions
*/
/**
 * @brief returns true if the character is an operator
 * @param c the character to check
 * 
 * note that the operators are: < > ; & | ( )
 */
int			isoperator(char c);

/*
Main function that we care about
*/
/**
 * @brief tokenise a string
 * @param str the string we need to tokenise
 * @returns list of tokens created from the string
 */
t_list		*tokenise(char *str);

/**
 * @brief get the string for a given token error.
 * @param err the token error to get the string from
 * @returns constant char representation of the error
 */
const char	*token_err_type_to_string(t_tokerr err);

/**
 * @brief print a token error (without a newline)
 * @param err the error to print
 */
void		print_token_error(t_tokerr err);

/**
 * @brief validate and cleanse a token list
 * @param tokens the token list
 * @returns a token error value
 * 
 * validation has a few steps (and these need to be updated) and 
 * when an error is found this function returns immediately.
 * 
 * cleansing just strips quotes from word tokens, but im not sure
 * if we should actually be doing this here or if it would be better 
 * suited to being done at the command prep stage
 */
t_tokerr	cleanse_validate_tokens(t_list *tokens);

#endif
