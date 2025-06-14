/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:43:25 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/14 17:06:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/v_dbg.h"

void		dbg_add_token_list(struct s_dbg_info *info, t_list *tk)
{
	t_list *node;

	node = tk;
	while (node)
	{
		dbg_add_token(info, node->content);
		node = node->next;
	}
}

void		dbg_add_ast(struct s_dbg_info *info, t_astnode *head)
{
	if (!head)
		return ;
	dbg_add_nodes(info, head);
	dbg_add_ast(info, head->left_node);
	dbg_add_ast(info, head->right_node);
}
