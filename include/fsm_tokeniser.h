/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:02:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/24 13:42:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_TOKENISER_H
# define FSM_TOKENISER_H

# include "libft.h"
# include <stdio.h>

# define TRNSCOUNT 38

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
	/// Just pased a dash 
	
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
	/// redirect to an fd isntead of a file n>&m
	TOK_REDIR_FD,
	// ERROR in case we need to signal to the rest of the program
	TOK_ERR,
	/// count of total token types
	TOK_COUNT
};

/**
 * @brief token type struct, provides information about a token
 * @param type the type of this token
 * @param raw the raw string for the token
 * @param heredoc_delim This token is a heredoc deliminator
 * @param redirect_file this token is a filename for a redirect
 * @param quotes_removed if the quotes in the raw string have been removed
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
	/// the type of this token
	t_tokentype	type;
	/// the raw token string
	char		*raw;
	/// flag this token as a heredoc deliminator
	int			heredoc_delim;
	/// flag this token as a filename for a redirect
	int			redirect_file;
	/// flag if the quotes have been removed
	int			quotes_removed;
	/// flag if the variables have been expanded
	int			variables_expanded;
};

/**
 * @brief internal struct for the tokeniser
 * 
 * @param i_start the index of the start of the current token
 * @param i_end the end index of the current token
 * @param curr_type the type of the current token
 * @param quote_mode the quote mode we are currently in
 * @param prev_line this is only for the case of the unfinished string
 * @param curr_token malloc'd token, populated when next token type is found
 * 
 */
typedef struct s_tokint			t_tokint;
struct s_tokint
{
	/// the index of the start of the current token
	size_t			i_start;
	/// the index of the end of the current token
	size_t			i_end;
	/// the type of the current token
	t_tokentype		curr_type;
	/// the quote mode we are currently in
	t_quote_mode	quote_mode;
	/// any data required from the previous line
	char			*prev_line;
	/// malloc'd token, needs to be pop'd
	t_token			*curr_token;
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
	// PARSER FATAL
	PARSE_FATAL,
	// nothing created from input 
	PARSE_NOTHING,
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
 * @param ST_CONT Continue state
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
	/// Continue State
	ST_CONT,
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
	/// the state we are transitioning from
	t_fsmstate	from_state;
	/// the accepted token types
	char		*token_types;
	/// the resulting state
	t_fsmstate	too_state;
};

/**
 * @brief the finite state machine for parsing
 * 
 * @param state the current fsm state
 * @param retcode the current return code
 * @param tokens the current list of tokens
 * @param paren_count the count of parenthesis
 * @param tok_int the internal tokeniser data
 * @param str_cond a string representing the state of the parser
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
	/// the current state of the fsm
	t_fsmstate		state;
	/// the previous state of the fsm
	t_fsmstate		last_state;
	/// the return code of the fsm
	t_tokretcode	retcode;
	/// the token list
	t_list			*tokens;
	/// the count of open parenthesis
	long int		paren_count;
	/// the internal tokeniser data
	t_tokint		tok_int;
	void			*debuginfo;
	/// a string representation of the condition upon return
	char			*str_cond;
};

/**
 * @brief reset the tokeniser removing all data in it for another run.
 * 
 * @param tokeniser the tokeniser struct
 */
void			reset_tokeniser(t_tokint *tokeniser);

/**
 * @brief reset the finite state machine parser completely
 * 
 * @param fsm the finite state machine struct
 */
void			reset_fsm(t_fsmdata *fsm);

/**
 * @brief Check if a transition from the current state is possible with
 * the next token
 * 
 * @param current_state the current state of the finite state machine
 * @param next_token the next token type
 * @return t_fsmstate the next state for the finite state machine
 * 
 * @note
 * A state of ST_WRNG means there was no transition found but not
 * that we are in a erroneous state as some wrong states can be
 * recovered.
 */
t_fsmstate		fsm_check_transition(const t_fsmstate current_state,
					const t_tokentype next_token);

/**
 * @brief pop the next token out of the tokeniser
 * 
 * @param tokeniser the tokeniser struct
 * @return t_token* the token from the tokeniser
 */
t_token			*tokeniser_pop_token(t_tokint *tokeniser);

/**
 * @brief get a string representation of a return code
 * 
 * @param code the code to stringify
 * @return const char* a string representation of the code
 */
const char		*tokretcode_str(const t_tokretcode code);

/**
 * @brief stringify a state from the finite state machine parser
 * 
 * @param state the state to stringify
 * @return const char* the string representation of the state
 */
const char		*fsmstate_str(const t_fsmstate state);

/**
 * @brief pop the list of tokens out of the finite state machine
 * 
 * @param fsm the finite state machine struct
 * @return t_list* the list of tokens parsed
 */
t_list			*fsm_pop_list(t_fsmdata *fsm);

/**
 * @brief find the token type of a given string
 * 
 * @param raw_token the raw token string to bin
 * @return t_tokentype the binned type of the token
 */
t_tokentype		bin_token(const char *raw_token);

/**
 * @brief Creates the internal next token from the start and end index
 * 
 * @param tokeniser the tokeniser struct
 * @param str the string being parsed
 * @return t_tokentype the next tokens type.
 */
t_tokentype		tokenise_type(t_tokint *tokeniser, const char *str);

/**
 * @brief Handles operators that may be 1 or 2 characters in length
 * 
 * @note
 * If we want to handle arbitrary fd redirection we may need to move the
 * handling of redirects to a new function.
 * 
 * This will move the end of the current token index in the tokeniser to 
 * reflect the length of the operator.
 * 
 * @param tokeniser the tokeniser struct
 * @param str the string being parsed
 */
t_tokentype			handle_operator(t_tokint *tokeniser, const char *str);

/**
 * @brief handle unclosed quote by duping the unfinished string
 * 
 * When a quote is left unclosed it needs to be closed by any of the
 * following lines, so we need to make sure we keep track of all the
 * data from the previous lines to append the following data. This function
 * will ensure that the data is stored in an appropriate place.
 * 
 * @param tokeniser the tokeniser struct
 * @param str the string being parsed
 * @return int 0 if error in allocation or 1 if ok
 */
int			handle_unclosed_quote(t_tokint *tokeniser, const char *str);

/**
 * @brief Utility function for making sure that we keep track of stats
 * 
 * Certain tokens need to trigger certain effects within the parser, 
 * like parenthesis need to be tracked so we dont end up with malformed
 * precendence.
 * 
 * @param fsm the finite state machine struct
 * @return int 1 if we are in a valid state 0 if not
 */
int				handle_token_type(t_fsmdata *fsm);

/**
 * @brief newlines inside subshells need to be handled differently.
 * 
 * newlines in subshells need to be handled differently depending on 
 * the token that came before the newline, if it is not an operator or 
 * a sequence then we need to insert a sequence.
 * 
 * @param fsm the finite state machine struct
 * @return 1 if ok, 0 if failed
 */
int			handle_subshell_newline(t_fsmdata *fsm);

/**
 * @brief is a character an operator
 * 
 * @param c character to check
 * @return int 1 if it is an operator 0 if not
 */
int				isoperator(const char c);

/**
 * @brief stringify a token type
 * 
 * @param type the token type to stringify
 * @return const char* the string of the token type
 */
const char		*token_type_to_string(const t_tokentype type);

/**
 * @brief print a token type string
 * 
 * @param type the type to print
 */
void			print_token_type(const t_tokentype type);

/**
 * @brief print a token in a table like row
 * 
 * @param token the token to print
 * @param column_width the width of the table columns
 */
void			print_token(const t_token *token, int column_width);

/**
 * @brief print a list of tokens in a table
 * 
 * @param list the list of tokens to print
 */
void			print_token_list(const t_list *list);

/**
 * @brief move the internal start index of the tokeniser to the
 * next non whitespace character.
 * 
 * @param tokeniser the tokeniser struct
 * @param str the string being parsed
 */
void			tokeniser_skip_whitespace(t_tokint *tokeniser, const char *str);

/**
 * @brief Create a token object
 * 
 * @param type the type of the token being created
 * @param raw_token the raw token data
 * @return t_token* an allocated token struct
 */
t_token			*create_token(const t_tokentype type, const char *raw_token);

/**
 * @brief destroy a token struct
 * 
 * @note
 * I can probably remove the del raw function from the following
 * as all tokens should have just an allocated string, so there is no
 * need to confuse the functions needed to destroy tokens.
 * 
 * @param token the token to destroy
 * @param del_raw a function to free the raw token string
 */
void			destroy_token(t_token *token, void (*del_raw)(void *));

/**
 * @brief free a list of tokens
 * 
 * @param list the list of tokens to free
 * @param del_raw a function to free the raw token string
 */
void			free_token_list(t_list *list, void (*del_raw)(void *));

/**
 * @brief free an array of tokens
 * 
 * @param vec the array to free 
 * @param del_raw function to free the raw token string
 */
void			free_token_vector(t_token **vec, void (*del_raw)(void *));

/**
 * @brief append an anonymous token to the token list
 * 
 * @note
 * anonymous here just means that it has no identity formed from
 * the parsed string, it is a token created artificially for one reason 
 * or another.
 * 
 * well its just used once at the moment to insert a sequence character.
 * 
 * @param fsm the finite state machine
 * @param type the type of the token to add
 * @param str the raw token contents
 * @return 1 if ok, 0 if failed
 */
int			append_anon_token(t_fsmdata *fsm, const t_tokentype type, const char *str);

/**
 * @brief Find the next token in the string and return its type
 * 
 * This function skips the start and end indexes to the next token,
 * then hands off the work to the function tokenise_type that uses
 * the data to create the next token struct and bin its type.
 * 
 * @param tokeniser the tokeniser struct
 * @param str the string being parsed
 * @return t_tokentype the type of the next token
 */
t_tokentype		next_token_type(t_tokint *tokeniser, const char *str);

/**
 * @brief Set the retcode object
 * 
 * @param fsm the finite state machine
 * @param code the return code to set
 * @param str_condition a condition string (optional)
 * @return t_tokretcode the return code that was set
 */
t_tokretcode	set_retcode(t_fsmdata *fsm,
					const t_tokretcode code, char *str_condition);

/**
 * @brief changes the state of the fsm
 * 
 * this will also set the last state to the current state, before
 * setting the current state to the next state.
 * 
 * @param fsm the fsm struct
 * @param next_state the next state to change too
 */
void			state_change(t_fsmdata *fsm, t_fsmstate next_state);

/**
 * @brief check what the current return code should be
 * 
 * We check all the cases that define what the return code should be
 * and determine what return code we need to send.
 * 
 * @param fsm the finite state machine struct
 * @return t_tokretcode the return code that needs to be sent
 */
t_tokretcode	correct_retcode(t_fsmdata *fsm);

/**
 * @brief Tokenise a string
 * 
 * When passed a string this function will either:
 * - Begin the tokenisation of the string
 * - Continue tokenising from the last continue condition
 * 
 * Parsing will populate the internal linked list with tokens,
 * this list can be popped when PARSE_OK.
 * 
 * If the string is in an incomplete state then a PARSE_CONT
 * will be returned and another string will be required to continue parsing.
 * 
 * When the parser has reached an state that is erroneous and that it cannot
 * recover from it will return PARSE_ERROR, the fsm can be cleaned manually
 * with a call to reset_fsm() or will reset itself when called again.
 * 
 * @param fsm the finite state machine struct
 * @param str the string to parse
 * @return t_tokretcode the condition state of the parse
 */
t_tokretcode	tokenise(t_fsmdata *fsm, const char *str);

#endif
