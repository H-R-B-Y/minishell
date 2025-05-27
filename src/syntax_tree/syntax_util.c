/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:34:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/26 17:52:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	destroy_ast(t_astnode **node)
{
	if (!node || !*node)
		return ;
	if ((*node)->left_node)
		destroy_ast(&(*node)->left_node);
	if ((*node)->right_node)
		destroy_ast(&(*node)->right_node);
	destroy_ast_node((*node));
	*node = 0;
	return ;
}
