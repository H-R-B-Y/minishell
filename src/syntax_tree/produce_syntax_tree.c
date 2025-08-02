/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   produce_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 18:35:52 by cquinter         ###   ########.fr       */
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
	meta.shell = shell;
	meta.rldata = &shell->rldata;
	meta.error = AST_ERR_NONE;
	head = ast_parse_seperators(&meta);
	if (meta.error == AST_ERR_NONE)
		*output = head;
	else if (meta.error == AST_ERR_FATAL)
		perror_exit(shell, "produce_ast");
	else
	{
		*output = 0;
		destroy_ast(&head);
	}
	return (meta.error);
}
