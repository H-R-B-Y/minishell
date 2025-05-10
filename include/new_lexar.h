/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexar.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 18:47:08 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_LEXAR_H
# define NEW_LEXAR_H

# include "libft.h"

# define ETOPTR (void *)(unsigned long int)
# define PTRTOE (int)(unsigned long int)
# define LCONT (PTRTOE ft_lstlast(meta->parse_stack)->content)
# define POPCONT free(ft_lstpop_back(&meta->parse_stack))

/*
start by checking the internal state ok the tokeniser.

if there is a continuation on the stack and the status is parse continue
	then we keep parsing as a continuation of the previous token list.
if there is continuation on the stack and the status is parse ok or parse error
	then we clear the stack and the token list, and parse afresh.

if there is a continuation on the stack and we are in parse continue,
	we get provided ONLY the next part of the line, not the entire line again,
	so we need to keep track of the list from the previous line.

we start with a loop to check that we have not got to the end of the string, 
	we have a start index and an end index for the current token, we increment the end ptr
	until it reaches an end token, if the end token is in a valid state then we take a substring
		if the end token is not valid:
			AND / OR / SEQ token and last token was not word or RPAREN
			RPAREN when there is no LPAREN on the stack
		then we set error status (and cleanup?)
	when we have the subtring we can bin the type and create t_token and add to list.

!! maybe we need to have a token for newline?
!! if we encounter a newline and we are not in a CONT state, then we
!! should replace the token with a sequence? 

!! if we encounter a newline character and we in a cont:
	EXPECTING WORD = replace the newline with space?
	EXPECT_HEREDOC = PARSE_ERROR
	EXPECT_QUOTE = newline is a word token
	EXPECT_DQUOTE = newline is a word token
	EXPECT_PAREN = newline becomes a ;

!! if we encounter a newline character and we not in a cont:
	this probably means that there is a heredoc?


!! we also need to be able to escape whitespace?

*/


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
	CONT_ERROR_COUNT
};

typedef struct s_tokeniserint	t_tokeniserinternal;
struct s_tokeniserint
{
	t_list		*parse_stack;
	t_tokstate	state;
	t_list		*tokens;
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
	TOK_NEWLINE, // Special case
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
	char		*trimmed;
	int			heredoc_deliminator;
};

t_token	*create_token(t_tokentype type, char *raw_token);
void	destroy_token(t_token *token, void (*del_raw)(void *));
void	free_token_list(t_list *list, void (*del_raw)(void *));
void	free_token_vector(t_token **vec, void (*del_raw)(void *));


void	print_token(t_token *token, int column_width);

t_list	*tokensise(t_tokeniserinternal *meta, char *str);

#endif