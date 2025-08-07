/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 17:50:24 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

# include "libft.h"
# include "./fsm_tokeniser.h"

typedef struct s_minishell		t_minishell;

typedef enum e_asterror			t_asterror;
enum e_asterror
{
	/// @brief There was no error
	AST_ERR_NONE,
	/// @brief There was a syntax error
	AST_ERR_SYNTAX,
	/// @brief Heredoc construction failed
	AST_ERR_HEREDOC_EXIT,
	/// @brief Caused when a filename gets a variable expanded in a horrible way
	AST_ERR_INVALID_REDIRECT,
	/// @brief FATAL error encountered
	AST_ERR_FATAL,
	/// @brief The count of error codes
	AST_ERR_COUNT,
};

/**
 * @brief I created this because i think we might need it, not because we do
 * 
 * I think when we build the command nodes and check for redirects we
 * should store the type of redirect
 */
typedef enum e_redir_type		t_redirect_type;
enum e_redir_type
{
	/// @brief Redirrct input
	REDIRECT_IN,
	/// @brief Redirect output
	REDIRECT_OUT,
	/// @brief Redirect output in append mode
	REDIRECT_OUT_A,
	/// @brief Redirect Heredoc
	REDIRECT_HD,
	/// @brief Redirect a fd to another
	REDIRECT_FD,
	/// @brief Count of redirect types
	REDIRECT_TYPE_COUNT,
};

enum	e_redirect_subtype
{
	/// @brief Redirect is for a file
	REDIR_FILE,
	/// @brief Redirect is for a file descriptor
	REDIR_FD,
	/// @brief This redirect is to close a file descriptor
	CLOSE_FD,
	/// @brief Count of redirect subtypes
	REDIR_SUBTYPE_COUNT,
};

// Need some information about what we are redirecting
// if we need a pipe we should store it here
// not sure if this will be usefull
/**
 * @brief this might be helpful later, but i am not sure if this is the best
 * way to do it so this is a placeholder
 * 
 * @param subtype subtype of the redirect
 * @param fd_map_from_fd The fd to map from
 * @param fd_map_to_fd The fd to map too
 * @param file_map_filename Name of the file that needs to be redirected
 * @param file_map_from_fd The FD created when opening the file
 * @param file_map_to_fd The FD to redirect the file too
 * @param type redirect type
 */
typedef struct s_redirect_desc	t_redirect_desc;
struct s_redirect_desc
{
	/// @brief The type of the redirect
	t_redirect_type			type;
	/// @brief The subtype of the redirect
	enum e_redirect_subtype	subtype;
	/// @brief Set of fds to restore
	int						*restore_fd;
	union
	{
		/// @brief Maps a file descriptor 
		struct s_none
		{
			/// @brief The fd to map from
			int			from_fd;
			/// @brief the fd to map too
			int			to_fd;
		}				fd_map;
		/// @brief Maps a file to a file descriptor
		struct s_none2
		{
			/// @brief name of file to map
			char		*name;
			/// @brief fd for opened file
			int			from_fd;
			/// @brief fd to map too
			int			to_fd;
		}				file_map;
	};
};

void			destroy_redirect(t_redirect_desc *n);

/**
 * @brief AST node types
 * @param AST_NONE None type (0)
 * @param AST_COMMAND Command type fork and run
 * @param AST_AND And type run left if succes run right
 * @param AST_OR Or type run left if not success run right
 * @param AST_SEQ Sequence type run left and right (depends on token)
 * @param AST_PIPE Pipe type open a pipe fork for left node (write)
 * and right node (read)
 * @param AST_SUBSHELL Subshell fork and run
 * @param AST_TYPE_COUNT Number of types available
 */
typedef enum e_asttype			t_astype;
enum e_asttype
{
	/// @brief AST node is of type none
	AST_NONE,
	/// @brief AST node is for a command
	AST_COMMAND,
	/// @brief AST node is for an AND operator
	AST_AND,
	/// @brief AST node is for an OR operator
	AST_OR,
	/// @brief AST node is for a sequence type (; or &)
	AST_SEQ,
	/// @brief AST node is for a pipe (|)
	AST_PIPE,
	/// @brief AST node is for a subshell
	AST_SUBSHELL,
	/// @brief Count of AST types
	AST_TYPE_COUNT
};

/**
 * @brief ast node is a simple binary tree node with some meta data
 * @param type the type of the node
 * @param left_node the left child
 * @param right_node the right child
 * @param tokens The tokens that make up the node
 * @param token_arr_freeable The token list is freeable
 * @param token_count The count of the tokens
 * @param cmdv The argument array
 * @param cmd_i The index of the actual command path in cmdv
 * @param envp The environment array
 * @param genv_l IDK
 * @param return_value Return code from waitpid
 * @param return_code Actual number that the process returned
 */
typedef struct s_astnode		t_astnode;
struct	s_astnode
{
	/// @brief the type of the node
	t_astype	type;
	t_astnode	*left_node;
	/// @brief the left child
	t_astnode	*right_node;
	/// @brief the right child
	t_astype	from_type;
	/// @brief The tokens that make up the node
	t_token		**tokens;
	/// @brief The token list is freeable
	int			token_arr_freeable;
	/// @brief The count of the tokens
	size_t		token_count;
	/// @brief The argument array
	char		**cmdv;
	/// @brief The index of the actual command path in cmdv
	size_t		cmd_i;
	/// @brief	Command path passed to execve
	char		*cmd_path;
	/// @brief List of redirect descriptors
	t_list		*redirect;
	/// @brief The environment array
	char		**envp;
	/// @brief IDK 
	size_t		genv_l; // to delete???
	/// @brief Argument count
	int			argc;
	/// @brief Return code from waitpid
	int			return_value;
	/// @brief Actual number that the process returned
	short		return_code;
};

/**
 * @brief create a new tree node
 * @param type the type of the new node
 * @param token array of tokens pertaining to this node
 * @param left the left child node
 * @param right the right child node
 * @returns a new tree node (head allocated)
 */
t_astnode		*create_ast_node(t_astype type,
					t_token **token, t_astnode *left, t_astnode *right);

/**
 * @brief destroy a tree node (free it)
 * @param node the node the destroy
 */
void			destroy_ast_node(t_astnode *node);

/**
 * @brief internal struct for ast construction
 * @param tokens Token vector we are currently working on
 * @param shell Reference to the shell
 * @param rldata Reference to the internal readline loop data
 * @param error Error code for the AST constructor
 * @param consumed The count of tokens that have been consumed during the
 * construction
 */
struct s_ast_internal
{
	t_token			**tokens;
	t_minishell		*shell;
	t_readline_data	*rldata;
	enum e_asterror	error;
	size_t			consumed;
};

/**
 * @brief produce an abstract syntax tree
 * @param tokens vector array of tokens used to construct the tree
 * @param count count of tokens in the array (TODO:i dont think we need this)
 * @returns head node of the tree
 */
int				produce_ast(t_minishell *shell,
					t_token **tokens, t_astnode **output);

/**
 * @brief destroy abstract syntax tree
 * @param node the head node of the tree
 * I dont think i have actually written this function? 
 */
void			destroy_ast(t_astnode **node);

/**
 * @brief create a new ast node from seperators
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode		*ast_parse_seperators(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from and or tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode		*ast_parse_and_or(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from pipe token
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode		*ast_parse_pipe(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from command tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode		*ast_parse_command(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from subcommand tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode		*ast_parse_subcommand(struct s_ast_internal *meta);

/**
 * @brief consume contiguous word tokens into a single command token
 * @param meta the metadata struct containing info about the tree
 * @param node the ??? too tired cannot remember
 */
ssize_t			ast_consume_words(struct s_ast_internal *meta, t_astnode *node);

/**
 * @brief print the ast
 * @param head the head node of the tree
 * @param indent the indent to use for child nodes
 */
void			print_ast(const t_astnode *head, const char *indent);

/**
 * @brief Process for handling redirecting file descriptors
 * @param redirect The token that specifies the redirect
 */
t_redirect_desc	*handle_redirectfd(t_token *redirect);

/**
 * @brief Process for handling redirected files
 * @param redirect The token that specifies the redirect
 * @param filename The token that contains the filename
 */
t_redirect_desc	*handle_redirect(t_token *redirect, char *filename);

/**
 * @brief Process for handling heredoc 
 * @param meta The internal struct for the ast constructor
 * @param delim The heredoc deliminator
 * @param heredoc The token that specifies the heredoc
 */
t_redirect_desc	*handle_heredoc(struct s_ast_internal *meta,
					const char *delim);

/**
 * @brief private to ast internal are we able to continue consuming
 */
int				_continue_parsing(struct s_ast_internal *meta);

#endif
