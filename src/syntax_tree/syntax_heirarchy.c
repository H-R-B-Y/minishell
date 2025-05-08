/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_heirarchy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 12:34:14 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_astnode	*ast_parse_subcommand(struct s_ast_internal *meta)
{
	t_astnode	*me;

	me = create_ast_node(AST_SUBSHELL, 0, 0, 0);
	meta->consumed++;
	me->left_node = ast_parse_seperators(meta);
	if (meta->tokens[meta->consumed]->type != TOK_RPAREN)
	{
		printf("Syntax error");
		exit(1);
	}
	meta->consumed++;
	return (me);
}

t_astnode	*ast_parse_command(struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = 0;
	if (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed]->type == TOK_LPAREN)
		lr[0] = ast_parse_subcommand(meta);
	else if (meta->tokens[meta->consumed]
		&& (meta->tokens[meta->consumed]->type == TOK_WORD
			|| meta->tokens[meta->consumed]->type == TOK_HEREDOC
			|| meta->tokens[meta->consumed]->type == TOK_REDIR_IN
			|| meta->tokens[meta->consumed]->type == TOK_REDIR_OUT
			|| meta->tokens[meta->consumed]->type == TOK_REDIR_APPEND))
	{
		lr[0] = create_ast_node(AST_COMMAND, 0, 0, 0);
		meta->consumed += ast_consume_words(meta, lr[0]);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_pipe(struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_command(meta);
	while (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed]->type == TOK_PIPE)
	{
		lr[0] = create_ast_node(AST_PIPE,
				(t_token *[2]){meta->tokens[meta->consumed], 0}, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_command(meta);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_and_or(struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_pipe(meta);
	while (meta->tokens[meta->consumed]
		&& (meta->tokens[meta->consumed]->type == TOK_AND_IF
			|| meta->tokens[meta->consumed]->type == TOK_OR_IF))
	{
		if (meta->tokens[meta->consumed]->type == TOK_AND_IF)
			lr[0] = create_ast_node(AST_AND,
					(t_token *[2]){meta->tokens[meta->consumed], 0}, lr[0], 0);
		else if (meta->tokens[meta->consumed]->type == TOK_OR_IF)
			lr[0] = create_ast_node(AST_OR,
					(t_token *[2]){meta->tokens[meta->consumed], 0}, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_pipe(meta);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_seperators(struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_and_or(meta);
	while (meta->tokens[meta->consumed]
		&& (meta->tokens[meta->consumed]->type == TOK_AMP
			|| meta->tokens[meta->consumed]->type == TOK_AFTER))
	{
		lr[0] = create_ast_node(AST_SEQ,
				(t_token *[2]){meta->tokens[meta->consumed], 0}, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_and_or(meta);
	}
	return (lr[0]);
}
