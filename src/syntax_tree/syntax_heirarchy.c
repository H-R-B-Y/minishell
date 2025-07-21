/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_heirarchy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/21 17:52:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_astnode	*ast_parse_command(struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = 0;
	if (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed]->type == TOK_LPAREN)
		lr[0] = ast_parse_subcommand(meta);
	else if (meta->tokens[meta->consumed]
		&& ft_strchr("\1\3\4\5\6\17", meta->tokens[meta->consumed]->type))
	{
		lr[0] = create_ast_node(AST_COMMAND, 0, 0, 0);
		if (!lr[0])
			meta->error = AST_ERR_FATAL;
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
		lr[0] = create_ast_node(AST_PIPE, 0, lr[0], 0);
		if (!lr[0])
			meta->error = AST_ERR_FATAL;
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
			lr[0] = create_ast_node(AST_AND, 0, lr[0], 0);
		else if (meta->tokens[meta->consumed]->type == TOK_OR_IF)
			lr[0] = create_ast_node(AST_OR, 0, lr[0], 0);
		if (!lr[0])
			meta->error = AST_ERR_FATAL;
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
		lr[0] = create_ast_node(AST_SEQ, 0, lr[0], 0);
		if (!lr[0])
			meta->error = AST_ERR_FATAL;
		meta->consumed++;
		lr[0]->right_node = ast_parse_and_or(meta);
	}
	return (lr[0]);
}
