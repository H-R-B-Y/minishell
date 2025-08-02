/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_seq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:36:38 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/02 18:36:41 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_seq(t_minishell *shell, t_astnode *node)
{
	execute_ast(shell, node->left_node);
	execute_ast(shell, node->right_node);
	return (shell->return_code);
}