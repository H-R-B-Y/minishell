/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:02:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 12:10:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_TOKENISER_H
# define FSM_TOKENISER_H

# include "libft.h"
# include <stdio.h>

# define TRNSCOUNT 32

/*
This section covers the main token types, 
skipping the tokens, and binning the tokens
*/

/**
 * @brief quote modes that the tokeniser can be in
 * 
 */
typedef enum e_quote_mode		t_quote_mode;
enum e_quote_mode
{
	/// No quotes for current token
	QUOTE_NONE,
	/// We are in a single quote 
	QUOTE_SINGLE,
	/// We are in a double quote
	QUOTE_DOUBLE,
	/// Count of quote modes
	QUOTE_MODE_COUNT,
};

/**
 * @brief token types for tokens parsed from arguments
 * @warning DO NOT CHANGE THE ORDER HERE!!!!!!
 */
typedef enum e_tokentype		t_tokentype;
enum e_tokentype
{
	/// if token is returned there is an error
	TOK_NONE,
	/// word token can be cmd / file / arg / heredoc deliminator
	TOK_WORD,
	/// pipe token is just `|` pipe
	TOK_PIPE,
	/// redirect out `>` must be followed by a filename (word)
	TOK_REDIR_OUT,
	/// redirect append `>>` must be followed by a filename (word)
	TOK_REDIR_APPEND,
	/// redirect in `<` must be followed by a filename (word)
	TOK_REDIR_IN,
	/// heredoc `<<` must be followed by a word
	TOK_HEREDOC,
	/// after ; 
	TOK_AFTER,
	/// and if condition `&&`
	TOK_AND_IF,
	/// or if condition `||`
	TOK_OR_IF,
	/// left parenthesis `(`
	TOK_LPAREN,
	/// right parenthesis `)`
	TOK_RPAREN,
	/// background operator `&`
	TOK_AMP,
	/// end of input
	TOK_EOF,
	/// tokeniser error couldn't complete a string sequence
	TOK_INCOMPLETE_STRING,
	/// count of total token types
	TOK_COUNT
};

/**
 * @brief token type struct, provides information about a token
 * @param type the type of this token
 * @param raw the raw string for the token
 * @param heredoc_delim This token is a heredoc deliminator
 * @param redirect_file this token is a filename for a redirect
 * @param variables_expanded This token has had its variables expanded
 * 
 * @note
 * There is some funky things that need to happen with word tokens
 * in preprocessing, like a redirect file can be an expanded variable
 * but a heredoc deliminator cannot be.
 * 
 * Also variables can be expanded in double quotes but not single 
 * quotes, so when we do preprocessing we need to make sure of this.
 * 
 * Also there is the case of: 
 * let var=abc
 * 
 *  "'$var'" this should be result in 'abc'
 *  '"$var"' this should result in "$var"
 * 
 */
typedef struct s_token			t_token;
struct s_token
{
	t_tokentype	type;
	char		*raw;
	int			heredoc_delim;
	int			redirect_file;
	int			quotes_removed;
	int			variables_expanded;
};

/**
 * @brief internal struct for the tokeniser
 * 
 * @param index_start the index of the start of the current token
 * @param index_end the end index of the current token
 * @param current_type the type of the current token
 * @param quote_mode the quote mode we are currently in
 * @param previous_line this is only for the case of the unfinished string
 * @param current_token malloc'd token, populated when next token type is found
 * 
 */
typedef struct s_tokint			t_tokint;
struct s_tokint
{
	size_t			index_start;
	size_t			index_end;
	t_tokentype		current_type;
	t_quote_mode	quote_mode;
	char			*previous_line;
	t_token			*current_token;
};

/**
 * @brief tokeniser return codes to signal whether we are ready to run
 * 
 */
typedef enum e_tokretcode		t_tokretcode;
enum e_tokretcode
{
	/// Parsing was successful and fsm will contain a list of tokens
	PARSE_OK,
	/// Parsing needs to be continued on the next line
	PARSE_CONT,
	/// Parsing was not successful
	/// fsm will need clearing / will clear on next call
	PARSE_ERROR,
	/// Count of different return codes
	TOKENISER_RETURNCODE_COUNT
};

/**
 * @brief Finite list of states for the finite state machine parser
 * @param ST_WRNG Wrong state (not always an error depends on last token)
 * @param ST_STRT Starting state
 * @param ST_WORD Word state
 * @param ST_OPRA Operator state
 * @param ST_SEQ Sequence state
 * @param ST_LSSH Left subshell `(`
 * @param ST_RSSH Right subshell `)`
 * @param ST_HDOC Heredoc state
 * @param ST_REDR Redirect state
 * @param ST_END End state
 * @param STATE_COUNT Count of states 
 */
typedef enum e_fsmstate			t_fsmstate;
enum e_fsmstate
{
	/// Wrong state (not always an error depends on last token)
	ST_WRNG,
	/// Starting state
	ST_STRT,
	/// Word state
	ST_WORD,
	/// Operator state
	ST_OPRA,
	/// Sequence state
	ST_SEQ,
	/// Left subshell `(`
	ST_LSSH,
	/// Right subshell `)`
	ST_RSSH,
	/// Heredoc state
	ST_HDOC,
	/// Redirect state
	ST_REDR,
	/// End state
	ST_END,
	/// Count of states 
	STATE_COUNT
};

/**
 * @brief transition data
 * 
 * @param from_state the state we are transitioning from
 * @param token_types the list of accepted tokens
 * @param too_state the state the token results in
 * 
 * @note
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
 * @param str_condition a string (alloc'd) representing the state of the parser
 * 
 * @note
 * Really important that any updates to this struct are reflected in
 * the relevant functions:
 * fsm
 * reset_fsm
 * 
 */
typedef struct s_fsmdata		t_fsmdata;
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

void			reset_tokeniser(t_tokint *tokeniser);
void			reset_fsm(t_fsmdata *fsm);
t_fsmstate		fsm_check_transition(t_fsmstate current_state,
					t_tokentype next_token);
t_token			*tokeniser_pop_token(t_tokint *tokeniser);

const char		*tokretcode_str(t_tokretcode code);
const char		*fsmstate_str(t_fsmstate state);
t_list			*fsm_pop_list(t_fsmdata *fsm);

t_tokentype		bin_token(const char *raw_token);
t_tokentype		tokenise_type(t_tokint *tokeniser, char *str);

void			handle_operator(t_tokint *tokeniser, char *str);
void			handle_unclosed_quote(t_tokint *tokeniser, char *str);
int				handle_token_type(t_fsmdata *fsm);
void			handle_subshell_newline(t_fsmdata *fsm);

const char		*operators(void);
int				isoperator(char c);

const char		*token_type_to_string(t_tokentype type);
void			print_token_type(t_tokentype type);
void			print_token(t_token *token, int column_width);
void			print_token_list(t_list *list);

void			tokeniser_skip_whitespace(t_tokint *tokeniser, char *str);

t_token			*create_token(t_tokentype type, char *raw_token);
void			destroy_token(t_token *token, void (*del_raw)(void *));
void			free_token_list(t_list *list, void (*del_raw)(void *));
void			free_token_vector(t_token **vec, void (*del_raw)(void *));
void			append_anon_token(t_fsmdata *fsm, t_tokentype type, char *str);

t_tokentype		next_token_type(t_tokint *tokeniser, char *str);
t_tokretcode	set_retcode(t_fsmdata *fsm,
					t_tokretcode code, char *str_condition);
void			state_change(t_fsmdata *fsm, t_fsmstate next_state);
t_tokretcode	correct_retcode(t_fsmdata *fsm);
t_tokretcode	tokenise(t_fsmdata *fsm, char *str);

#endif
