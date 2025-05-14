/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 17:31:20 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

# include "libft.h"
# include "./fsm_tokeniser.h"
// # include "input_tokens.h"

/**
 * @brief I created this because i think we might need it, not because we do
 * 
 * I think when we build the command nodes and check for redirects we
 * should store the type of redirect
 */
typedef enum e_redir_type		t_redirect_type;
enum e_redir_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
	REDIRECT_HEREDOC,
};

// Need some information about what we are redirecting
// if we need a pipe we should store it here
// not sure if this will be usefull
/**
 * @brief this might be helpful later, but i am not sure if this is the best
 * way to do it so this is a placeholder
 * 
 * @param type redirect type
 * @param pipe pipe ends if applicable
 * @param from_fd is a readable fd to dup to input
 * @param to_fd is a writble fd to dup to output
 */
typedef struct s_redirect_desc	t_redirect_desc;
struct s_redirect_desc
{
	t_redirect_type	type;
	int				is_pipe;
	int				pipe[2];
	int				from_fd;
	int				to_fd;
};

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
	AST_NONE,
	AST_COMMAND,
	AST_AND,
	AST_OR,
	AST_SEQ,
	AST_PIPE,
	AST_SUBSHELL,
	AST_TYPE_COUNT
};

/**
 * @brief ast node is a simple binary tree node with some meta data
 * @param type the type of the node
 * @param left_node the left child
 * @param right_node the right child
 * @param tokens the tokens pertaining to the current node
 * @param token_count the count of tokens in the above array
 * @param cmdv char vector to store the command and args (only command nodes)
 * @param redirect (placeholder) not sure if this is going to be helpful
 * @param envp the environment for the command node
 */
typedef struct s_astnode		t_astnode;
struct	s_astnode
{
	t_astype	type;
	t_astnode	*left_node;
	t_astnode	*right_node;

	t_token		**tokens;
	size_t		token_count;

	char		**cmdv;
	t_list		*redirect; // store the redirect descriptors in the list.
	char		**envp;

	int			return_code;
};

/**
 * @brief create a new tree node
 * @param type the type of the new node
 * @param token array of tokens pertaining to this node
 * @param left the left child node
 * @param right the right child node
 * @returns a new tree node (head allocated)
 */
t_astnode	*create_ast_node(t_astype type,
				t_token **token, t_astnode *left, t_astnode *right);

/**
 * @brief destroy a tree node (free it)
 * @param node the node the destroy
 * @param del_cmdv function to delete the command vector (placeholder)
 * @param del_envp function to delete the command vector (placeholder)
 */
void		destroy_ast_node(t_astnode *node,
				void (*del_cmdv)(void *), void (*del_envp)(void *));

/**
 * @brief internal struct for ast construction
 * @param tokens token vector we are currently working on
 * @param count the count of the tokens? (TODO:please verify)
 * @param consumed the index of the next node to consume
 * @param left_node (placeholder) I dont think we need to keep this
 * @param right_node (placeholder) I dont think we need to keep this
 */
struct s_ast_internal
{
	t_token		**tokens;
	size_t		count;

	size_t		consumed;
	t_astnode	*left_node; // Might not be needed
	t_astnode	*right_node; // Might not be needed
};

/**
 * @brief produce an abstract syntax tree
 * @param tokens vector array of tokens used to construct the tree
 * @param count count of tokens in the array (TODO:i dont think we need this)
 * @returns head node of the tree
 */
t_astnode	*produce_ast(t_token **tokens, size_t count);

/**
 * @brief destroy abstract syntax tree
 * @param head the head node of the tree
 * I dont think i have actually written this function? 
 */
void		destroy_ast(t_astnode *head);

/**
 * @brief create a new ast node from seperators
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode	*ast_parse_seperators(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from and or tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode	*ast_parse_and_or(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from pipe token
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode	*ast_parse_pipe(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from command tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode	*ast_parse_command(struct s_ast_internal *meta);

/**
 * @brief create a new ast node from subcommand tokens
 * @param meta the metadata struct containing info about the tree.
 * @returns new ast node (head allocated)
 */
t_astnode	*ast_parse_subcommand(struct s_ast_internal *meta);

/**
 * @brief consume contiguous word tokens into a single command token
 * @param meta the metadata struct containing info about the tree
 * @param node the ??? too tired cannot remember
 */
size_t		ast_consume_words(struct s_ast_internal *meta, t_astnode *node);

/**
 * @brief print the ast
 * @param head the head node of the tree
 * @param indent the indent to use for child nodes
 */
void		print_ast(t_astnode *head, char *indent);

#endif
