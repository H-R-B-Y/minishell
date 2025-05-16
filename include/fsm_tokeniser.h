/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:02:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 10:53:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_TOKENISER_H
# define FSM_TOKENISER_H

# include "libft.h"
# include <stdio.h>

/*
This section covers the main token types, 
skipping the tokens, and binning the tokens
*/

typedef enum e_quote_mode	t_quote_mode;
enum e_quote_mode
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_MODE_COUNT,
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
	TOK_EOF,
	TOK_INCOMPLETE_STRING,
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
	int			heredoc_delim;
	int			quotes_removed;
	int			variables_expanded;
};

/**
 * @brief internal struct for the tokeniser
 * 
 * @param index_start the starting index for the current token
 * @param index_end the end index for the current token
 * @param current_type the type of the current token
 * @param quote_mode the current quote mode
 * @param current_string temp storage
 * 
 */
typedef struct s_tokint	t_tokint;
struct s_tokint
{
	size_t			index_start;
	size_t			index_end;
	t_tokentype		current_type;
	t_quote_mode	quote_mode;
	char			*previous_line;
	t_token			*current_token;
};

t_tokint	*tokeniser(void);

/*
This section covers the main fsm and creating the token list.
*/

typedef enum e_tokretcode	t_tokretcode;
enum e_tokretcode
{
	PARSE_OK,
	PARSE_CONT,
	PARSE_ERROR,
	TOKENISER_RETURNCODE_COUNT
};


typedef enum e_fsmstate	t_fsmstate;
enum e_fsmstate
{
	ST_WRNG,
	ST_STRT,
	ST_WORD,
	ST_OPRA,
	ST_SEQ,
	ST_LSSH,
	ST_RSSH,
	ST_HDOC,
	ST_REDR,
	ST_END,
	STATE_COUNT
};

# define TRNSCOUNT 32

/**
 * @brief transition data
 * 
 * @param from_state the state we are transitioning from
 * @param token_types the list of accepted tokens
 * @param too_state the state the token results in
 * 
 * This is an important part of the tokeniser FSM, 
 * we keep all known valid transitions in a list
 * somewhere and we can refer to the list whenever we need
 * to know if a token is a valid continuation of the previous state
 */
typedef struct s_fsmtransition	t_fsmtransition;
struct s_fsmtransition
{
	t_fsmstate	from_state;
	char		*token_types;
	t_fsmstate	too_state;
};

/**
 * @brief the finite state machine for parsing
 * 
 * @param state the current fsm state
 * @param retcode the current return code
 * @param tokens the current list of tokens
 * @param paren_count the count of parenthesis
 * @param tokeniser_internals the internal tokeniser data
 * 
 * Really important that any updates to this struct are reflected in
 * the relevant functions:
 * fsm
 * reset_fsm
 * 
 */
typedef struct s_fsmdata	t_fsmdata;
struct s_fsmdata
{
	t_fsmstate		state;
	t_fsmstate		last_state;
	t_tokretcode	retcode;
	t_list			*tokens;
	long int		paren_count;
	t_tokint		tokeniser_internals;
	char			*str_condition;
};


t_fsmdata	*fsm(void);
void	reset_fsm(void);
const t_fsmtransition	*_fsm_trns(void);
t_fsmstate	fsm_check_transition(t_fsmstate current_state,
				t_tokentype next_token);


t_tokretcode	tokenise(char *str);


t_token	*tokeniser_pop_token(void);

/**
 * @brief check if a charcter is an operator
 * 
 * This function might not be needed anymore
 * 
 * @param c the character to check
 * @return int true of false flag
 */
int		isoperator(char c);

const char *tokretcode_str(t_tokretcode code);
const char *fsmstate_str(t_fsmstate state);
t_list	*fsm_pop_list(void);

void	tokeniser_skip_whitespace(char *str);

t_token	*create_token(t_tokentype type, char *raw_token);
void	destroy_token(t_token *token, void (*del_raw)(void *));
void	free_token_list(t_list *list, void (*del_raw)(void *));
void	free_token_vector(t_token **vec, void (*del_raw)(void *));
void	append_anon_token(t_tokentype type, char *str);

t_tokentype	bin_token(const char *raw_token);
t_tokentype	tokenise_type(char *str);


void	handle_operator(char *str);
void	handle_unclosed_quote(char *str);
int		handle_token_type(void);
void	handle_subshell_newline(void);

void	state_change(t_fsmstate next_state);

const char	*token_type_to_string(t_tokentype type);
void		print_token_type(t_tokentype type);
void		print_token(t_token *token, int column_width);
void		print_token_list(t_list *list);


#endif
