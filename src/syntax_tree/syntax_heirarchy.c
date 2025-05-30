/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_heirarchy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/30 19:45:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_astnode	*ast_parse_subcommand(t_minishell *shell, struct s_ast_internal *meta)
{
	t_astnode	*me;

	me = create_ast_node(AST_SUBSHELL, 0, 0, 0);
	meta->consumed++;
	me->left_node = ast_parse_seperators(shell, meta);
	if ((meta->tokens[meta->consumed]
			&& meta->tokens[meta->consumed]->type != TOK_RPAREN)
		|| !meta->tokens[meta->consumed])
	{
		printf("Syntax error");
		exit(1);
	}
	meta->consumed++;
	return (me);
}

// && (meta->tokens[meta->consumed]->type == TOK_WORD // 1
// 	|| meta->tokens[meta->consumed]->type == TOK_REDIR_OUT // 3 
// 	|| meta->tokens[meta->consumed]->type == TOK_REDIR_APPEND // 4
// 	|| meta->tokens[meta->consumed]->type == TOK_REDIR_IN // 5
// 	|| meta->tokens[meta->consumed]->type == TOK_HEREDOC // 6
// 	|| meta->tokens[meta->consumed]->type == TOK_REDIR_FD)) // 17
t_astnode	*ast_parse_command(t_minishell *shell, struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = 0;
	if (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed]->type == TOK_LPAREN)
		lr[0] = ast_parse_subcommand(shell, meta);
	else if (meta->tokens[meta->consumed]
		&& ft_strchr("\1\3\4\5\6\17", meta->tokens[meta->consumed]->type))
	{
		lr[0] = create_ast_node(AST_COMMAND, 0, 0, 0);
		meta->consumed += ast_consume_words(shell, meta, lr[0]);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_pipe(t_minishell *shell, struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_command(shell, meta);
	while (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed]->type == TOK_PIPE)
	{
		lr[0] = create_ast_node(AST_PIPE,
				0, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_command(shell, meta);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_and_or(t_minishell *shell, struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_pipe(shell, meta);
	while (meta->tokens[meta->consumed]
		&& (meta->tokens[meta->consumed]->type == TOK_AND_IF
			|| meta->tokens[meta->consumed]->type == TOK_OR_IF))
	{
		if (meta->tokens[meta->consumed]->type == TOK_AND_IF)
			lr[0] = create_ast_node(AST_AND,
					0, lr[0], 0);
		else if (meta->tokens[meta->consumed]->type == TOK_OR_IF)
			lr[0] = create_ast_node(AST_OR,
					0, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_pipe(shell, meta);
	}
	return (lr[0]);
}

t_astnode	*ast_parse_seperators(t_minishell *shell, struct s_ast_internal *meta)
{
	t_astnode	*lr[2];

	lr[0] = ast_parse_and_or(shell, meta);
	while (meta->tokens[meta->consumed]
		&& (meta->tokens[meta->consumed]->type == TOK_AMP
			|| meta->tokens[meta->consumed]->type == TOK_AFTER))
	{
		lr[0] = create_ast_node(AST_SEQ,
				0, lr[0], 0);
		meta->consumed++;
		lr[0]->right_node = ast_parse_and_or(shell, meta);
	}
	return (lr[0]);
}
