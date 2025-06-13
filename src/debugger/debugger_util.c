/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:43:25 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/06 12:43:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/v_dbg.h"

void	dbg_add_token_list(t_list *tk)
{
	t_list *node;

	node = tk;
	while (node)
	{
		dbg_add_token(static_debug_info(), node->content);
		node = node->next;
	}
}

void	dbg_add_ast(t_astnode *head)
{
	if (!head)
		return ;
	dbg_add_nodes(static_debug_info(), head);
	dbg_add_ast(head->left_node);
	dbg_add_ast(head->right_node);
}
