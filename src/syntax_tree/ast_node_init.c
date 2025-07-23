/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/23 14:59:05 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	destroy_redirect(t_redirect_desc *n)
{
	if (!n)
		return ;
	if (n->subtype == REDIR_FILE)
		free(n->file_map.filename);
	free(n);
}

t_astnode	*create_ast_node(t_astype type,
	t_token **token, t_astnode *left, t_astnode *right)
{
	t_astnode	*me;

	me = calloc(1, sizeof(t_astnode));
	if (!me)
		return (NULL);
	me->type = type;
	me->left_node = left;
	me->right_node = right;
	me->tokens = token;
	me->token_count = ft_arrlen((void *)token);
	return (me);
}

void	close_fds_needed(t_list	*redirects)
{
	t_redirect_desc	*desc;
	t_list			*node;

	if (!redirects)
		return ;
	node = redirects;
	while (node)
	{
		desc = node->content;
		node = node->next;
		if (!desc)
			continue ;
		if (desc->subtype == REDIR_FILE
			&& desc->file_map.from_fd > 2)
// note, im not sure we need this, it may
// be better to add a flag to the redirct node,
// to atleast tell us if it was initialized
// (if it was initialized then closing 0,1,2 is probably what the user intended)
			close(desc->file_map.from_fd);
	}
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
	close_fds_needed(node->redirect);
	if (node->redirect)
		ft_lstclear(&node->redirect, (void *)destroy_redirect);
	free(node);
}
