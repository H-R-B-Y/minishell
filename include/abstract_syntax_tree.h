/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:42:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:23:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

# include "libft.h"
# include "input_tokens.h"

typedef enum e_redir_type		t_redirect_type;
enum e_redir_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_HEREDOC,
};

// Need some information about what we are redirecting
// if we need a pipe we should store it here
// not sure if this will be usefull
typedef struct s_redirect_desc	t_redirect_desc;
struct s_redirect_desc
{
	t_redirect_type	type;
	int				is_pipe;
	int				pipe[2];
	int				from_fd;
	int				to_fd;
};

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

t_astnode	*create_ast_node(t_astype type,
				t_token **token, t_astnode *left, t_astnode *right);
void		destroy_ast_node(t_astnode *node,
				void (*del_cmdv)(void *), void (*del_envp)(void *));

// internal struct for keeping track of what has been consumed? 

struct s_ast_internal
{
	t_token		**tokens;
	size_t		count;

	size_t		consumed;
	t_astnode	*left_node; // Might not be needed
	t_astnode	*right_node; // Might not be needed
};

t_astnode	*produce_ast(t_token **tokens, size_t count);
void		destroy_ast(t_astnode *head);

t_astnode	*ast_parse_seperators(struct s_ast_internal *meta);
t_astnode	*ast_parse_and_or(struct s_ast_internal *meta);
t_astnode	*ast_parse_pipe(struct s_ast_internal *meta);
t_astnode	*ast_parse_command(struct s_ast_internal *meta);
t_astnode	*ast_parse_subcommand(struct s_ast_internal *meta);

size_t		ast_consume_words(struct s_ast_internal *meta, t_astnode *node);

void		print_ast(t_astnode *head, char *indent);

#endif
