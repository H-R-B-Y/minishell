/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:13:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/30 20:44:05 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(t_minishell *shell, t_astnode *node)
{
	if (!node)
			return (-1);
	// if (node->type == subshell)
	// 	execute_subshell(node);
	// else if (node->type == AND || OR)
	// 	execute_logical(node);
	else if (node->type == AST_PIPE)
		execute_pipe(shell, node);
	// else if (node->type == SEQ)
	// 	execute_sequence(node);
	else if (node->type == AST_COMMAND)
		return (execute_command(shell, node));
	return (-1);
}
