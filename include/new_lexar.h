/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexar.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 12:04:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_LEXAR_H
# define NEW_LEXAR_H

# include "libft.h"

/**
 * the following definitions should probably be moved out of the global scope!
 * 
 */

# define ETOPTR (void *)(unsigned long int)
# define PTRTOE (int)(unsigned long int)
# define LCONT (PTRTOE ft_lstlast(meta->parse_stack)->content)
# define POPCONT free(ft_lstpop_back(&meta->parse_stack))

typedef enum e_tokeniserstate	t_tokstate;
enum e_tokeniserstate
{
	PARSE_OK,
	PARSE_CONTINUE,
	PARSE_ERROR,
	TOKENISER_STATES
};

typedef enum e_tokparsecont	t_tokcont;
enum e_tokparsecont
{
	NONE,
	EXPECT_WORD, // && / || expect word or sequence
	EXPECT_HEREDOC, // << expects a word
	EXPECT_QUOTE, // expects '
	EXPECT_DQUOTE, // expects " but not \"
	EXPECT_PAREN, // expects )
	ESCAPED_NEWLINE,
	CONT_ERROR_COUNT
};

typedef struct s_tokeniserint	t_tokeniserinternal;
struct s_tokeniserint
{
	t_list		*parse_stack;
	t_tokstate	state;
	t_list		*tokens;
	char		*error_reason;
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
 * 
 * @warning DO NOT CHANGE THE ORDER HERE!!!!!!
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
 * @brief token type struct, provides information about a token
 * @param type the token type
 * @param raw the raw token string
 * @param heredoc_deliminator flag for if this string is the heredoc end
 * of line deliminator (Might remove)
 */
typedef struct s_token		t_token;
struct s_token
{
	t_tokentype	type;
	char		*raw;
	int			heredoc_deliminator;
};

/**
 * @brief Create a token object
 * 
 * @param type the token type for the new token
 * @param raw_token the raw token string
 * @return t_token* allocated new token
 */
t_token	*create_token(t_tokentype type, char *raw_token);

/**
 * @brief delete a token
 * 
 * Deletes a token and optionally free's the raw string 
 * data in the token. 
 * 
 * When a token is destroyed it's stripped data is free'd also.
 * 
 * @param token the token to delete
 * @param del_raw (optional) function to free the raw string
 */
void	destroy_token(t_token *token, void (*del_raw)(void *));

/**
 * @brief free a linked list of tokens
 * 
 * @param list the list of tokens to free
 * @param del_raw (optional) function to free the raw strings
 */
void	free_token_list(t_list *list, void (*del_raw)(void *));

/**
 * @brief free a token list
 * 
 * @param vec the list of tokens to free
 * @param del_raw (optional) function to free the raw string
 */
void	free_token_vector(t_token **vec, void (*del_raw)(void *));

/**
 * @brief print a token in a formatted column
 * 
 * @param token the token to print out
 * @param column_width the width of the columns
 */
void	print_token(t_token *token, int column_width);

/**
 * @brief tokenise a given string
 * 
 * Parsing the token list can be a multi-step process
 * once the function has returned you will need to check
 * the internal struct's state which will be one of three
 * potential states:
 * - PARSE_OK - this means the parsing was successful
 * - PARSE_CONTINUE - this means the tokens were left in a partial state
 * - PARSE_ERROR - this means the input string was invalid
 * 
 * @param meta the internal parsing struct
 * @param str the string to parse
 * @return t_list* either a list of tokens or NULL
 */
t_list	*tokenise(t_tokeniserinternal *meta, char *str);

/**
 * @brief skip a quoted string
 * 
 * This function is a bit funky, 
 * if we are parsing a newline with 
 * unclosed quotes from the previous line
 * this is not the function to use.
 * 
 * @param str the string pointer we are tokenising
 * @param i the index in the string we are starting at
 * @param quote the quote character we are trying to close
 * @return size_t the count of characters up to and including the closing quote
 */
size_t	skip_quoted(char *str, size_t i, char quote);

/**
 * @brief skip a potential double symbol
 * 
 * Double symbols are characters that MIGHT
 * be followed by a matching symbol representing a different
 * type of token, for example pipe | could actually be a
 * OR token if the following character is another |
 * 
 * @param str the string we are tokenising
 * @param i the index in the string we are looking at
 * @return size_t either 1 or 2 for single or double
 */
size_t	skip_potential_double(char *str, size_t i);

/**
 * @brief skip a word token
 * 
 * Words are quite difficult, this is one word: hello
 * this is also one word: hello"world"
 * but this is two words: hello world
 * and this is one word: hello" world"
 * 
 * @param meta the internal parsing struct
 * @param str the string we are tokenising
 * @param i the index in the string we are looking at
 * @param quote a optional quote character used when continuing from a newline
 * @return size_t the number of characters in the word token
 */
size_t	skip_word(t_tokeniserinternal *meta, char *str, size_t i, char quote);

/**
 * @brief check if a charcter is an operator
 * 
 * This function might not be needed anymore
 * 
 * @param c the character to check
 * @return int true of false flag
 */
int		isoperator(char c);

/**
 * @brief check if a quote is closed
 * 
 * This might not be needed anymore,
 * it was initially implemented for escaped quotes, but 
 * I have given up on trying to make that work.
 * 
 * @param str the string we are looking at
 * @param i the index of the potential closing quote
 * @param quote the quote we are trying to match
 * @return int true or false flag
 */
int		quote_closed(char *str, size_t i, char quote);

/**
 * @brief Check a token for a potential continuation state
 * 
 * @param meta the internal struct for parsing
 * @param type the token type of the token we are checking.
 */
void	update_continuation(t_tokeniserinternal *meta, t_tokentype type);

/**
 * @brief skip whitespace 
 * 
 * @param str the string we are tokenising
 * @param i the index in the string we are starting from
 * @return size_t the number of characters we can skip
 */
size_t	token_skip_whitespace(char *str, size_t i);

/**
 * @brief generic function to skip all tokens
 * 
 * this is the parent function to all the skipping sub functions
 * this function will determine what needs to be skipped in order to
 * produce the next token
 * 
 * @param meta the internal struct for parsing
 * @param str the string we are currently tokenising
 * @param i the index in the string that we are working from
 * @return size_t the number of characters we can skip to complete a token
 */
size_t	skip_token(t_tokeniserinternal *meta, char *str, size_t i);

/**
 * @brief find the type of the token and create a new token struct
 * 
 * binning a token just means we are finding which bin it goes in
 * by getting the type of the token we can then create a new token 
 * struct and add it to a list item so it can later be appended to
 * the token list.
 * 
 * @param meta the internal parsing data
 * @param raw_token the raw token string to bin
 * @return t_list* a new list item containing the new token struct
 */
t_list	*bin_and_create_token(t_tokeniserinternal *meta, char *raw_token);

/**
 * @brief create an anonymous token and append it to the token list
 * 
 * by anonymous here i just mean that the token doesnt have to be part of the
 * actual string being parsed
 * 
 * @param meta the internal data for the parser
 * @param type the type of the anonymous token
 * @param str the raw string data for the anonymous token
 */
void	append_anon_token(t_tokeniserinternal *meta,
			t_tokentype type, char *str);

/**
 * @brief internal function for skipping quoted strings
 * 
 * this code is black magic i dont know how to explain lol
 * 
 * basically we cant just skip quotes because we need to check a few things
 * if we are on a newline and we are trying to close quotes on a previous line
 * this function will make sure that that happens, if we are not doing that then 
 * we can continue skipping quotes as usual.
 * 
 * The difference is subtle but the quote argument is what allows us to close
 * quotes from a previous line.
 * 
 * @param meta the internal data for the parser
 * @param str the string we are tokenising
 * @param i the index of the string we are parsing from
 * @param quote (optional) quote that needs to be closed from a previous line
 * @return size_t the number of chars in the quoted string including the qutoes
 */
size_t	_skip_quoted_internal(t_tokeniserinternal *meta, char *str,
			size_t i, char quote);

/**
 * @brief begin parsing a string, we need to ensure the internal data is clean
 * 
 * This function does not return anything but will populate the list
 * inside of the meta struct.
 * 
 * @param meta internal parsing data
 * @param str the string we are parsing
 */
void	_begin_parsing(t_tokeniserinternal *meta, char *str);

/**
 * @brief assist in closing quotes or parenthesis on newline
 * 
 * again here this is a bad function, but not really sure what else i can do
 * if there is a closing quote or parenthesis from the previous line
 * it needs to be handled in a specific way before we let the parser continue
 * parsing the rest of the line.
 * 
 * @param meta the internal metadata for the parser
 * @param str the string we are parsing
 * @return size_t the number of characters to skip
 */
size_t	_parse_to_close(t_tokeniserinternal *meta, char *str);

void	handle_end_token(t_tokeniserinternal *meta, t_list *last_token,
			t_list *next_token);
void	check_single_error(t_tokeniserinternal *meta, t_list *next_token);
void	check_for_parse_errors(t_tokeniserinternal *meta, t_list *last_token,
			t_list *next_token);


void	 tokeniser_set_error(t_tokeniserinternal *meta, char *error);

#endif