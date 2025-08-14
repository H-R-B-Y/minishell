/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:36:27 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:39:50 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_logical(t_minishell *shell, t_astnode *node)
{
	execute_ast(shell, node->left_node);
	if ((node->type == AST_AND && shell->return_code == 0)
		|| (node->type == AST_OR && shell->return_code != 0))
		execute_ast(shell, node->right_node);
	return (shell->return_code);
}
