/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/07 15:49:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(t_minishell *shell, t_astnode *node)
{
	if (!node)
			return (-1);
	if (node->type == AST_SUBSHELL)
		execute_subshell(shell, node);
	else if (node->type == AST_AND || node->type == AST_OR)
		execute_logical(shell, node);
	else if (node->type == AST_PIPE)
		execute_pipe(shell, node);
	else if (node->type == AST_SEQ)
		execute_seq(shell, node);
	else if (node->type == AST_COMMAND)
		return (execute_command(shell, node));
	return (-1);
}
