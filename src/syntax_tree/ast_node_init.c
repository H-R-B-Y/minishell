/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/02 16:31:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	temp(void *n)
{
	(void)n;
	printf("This function has not been implemented yet");
}

t_astnode	*create_ast_node(t_astype type, t_token *token, t_astnode *left, t_astnode *right)
{
	t_astnode	*me;

	me = malloc(sizeof(t_astnode));
	ft_bzero(me, sizeof(t_astnode));
	me->type = type;
	me->left_node = left;
	me->right_node = right;
	me->token = token;
	return (me);
}
void	destroy_ast_node(t_astnode *node,
	void (*del_cmdv)(void *),
	void (*del_envp)(void *))
{
	if (!node)
		return ;
	if (del_cmdv && node->cmdv)
		del_cmdv(node->cmdv);
	if (del_envp && node->envp)
		del_envp(node->envp);
	if (node->redirect)
		ft_lstclear(&node->redirect, temp);
	free(node);
}
