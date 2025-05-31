/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 15:09:58 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	temp(void *n)
{
	(void)n;
	printf("This function has not been implemented yet");
}

t_astnode	*create_ast_node(t_astype type,
	t_token **token, t_astnode *left, t_astnode *right)
{
	t_astnode	*me;

	me = malloc(sizeof(t_astnode));
	ft_bzero(me, sizeof(t_astnode));
	me->type = type;
	me->left_node = left;
	me->right_node = right;
	me->tokens = token;
	me->token_count = ft_arrlen((void *)token);
	return (me);
}

void	destroy_ast_node(t_astnode *node)
{
	if (!node)
		return ;
	if (node->token_arr_freeable)
		free(node->tokens);
	if (node->cmdv)
		ft_arrclear((void *)node->cmdv, free);
	if (node->envp)
		ft_arrclear((void *)node->envp, free);
	if (node->redirect)
		ft_lstclear(&node->redirect, temp);
	free(node);
}
