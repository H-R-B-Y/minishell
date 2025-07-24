/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   produce_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/24 14:05:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	produce_ast(t_minishell *shell, t_token **tokens, t_astnode **output)
{
	struct s_ast_internal	meta;
	t_astnode				*head;

	if (!tokens || !*tokens)
		return (AST_ERR_SYNTAX);
	meta.tokens = tokens;
	meta.consumed = 0;
	meta.left_node = 0;
	meta.shell = shell;
	meta.right_node = 0;
	meta.rldata = &shell->rldata;
	meta.error = AST_ERR_NONE;
	head = ast_parse_seperators(&meta);
	if (meta.error == AST_ERR_NONE)
		*output = head;
	else if (meta.error == AST_ERR_FATAL)
		perror_exit(shell, "minishell:produce_ast");
	else
	{
		*output = 0;
		destroy_ast(&head);
	}
	return (meta.error);
}
