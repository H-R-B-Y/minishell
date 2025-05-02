/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/02 12:18:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

# include "libft.h"

typedef enum e_asttype	t_astype;
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

typedef enum e_redir_type	t_redirect_type;
enum e_redir_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_HEREDOC,
};

typedef struct s_redirect_desc	t_redirect_desc;
struct s_redirect_desc
{
	t_redirect_type	type;
	// Need some information about what we are redirecting
	// if we need a pipe we should store it here
	
	// not sure if this will be usefull
	int	is_pipe;
	int	pipe[2];

	// Just gonna use some placeholders
	int	from_fd;
	int	to_fd;
};

typedef struct s_astnode	t_astnode;
struct	s_astnode
{
	t_astype	type;
	t_astnode	*left_node;
	t_astnode	*right_node;

	char		**cmdv;
	t_list		*redirect; // store the redirect descriptors in the list.
	char		**envp;
};

// internal struct for keeping track of what has been consumed? 

struct s_ast_internal
{
	char	**tokens;
	size_t	count;

	size_t	consumed;
	t_astnode	*left_node; // Might not be needed
	t_astnode	*right_node; // Might not be needed
};

t_astnode	produce_ast(char **tokens, size_t count);

t_astnode	ast_parse_seperators();
t_astnode	ast_parse_and_or();
t_astnode	ast_parse_pipe();
t_astnode	ast_parse_command();
t_astnode	ast_parse_subcommand();

#endif
