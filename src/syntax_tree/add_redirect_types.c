/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:25:05 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 10:16:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**cmdv_prep(t_minishell *shell, t_astnode *node);

static char	**cheeky_expand(t_minishell *shell, t_token *tok)
{
	t_astnode	node;

	node = (t_astnode){.tokens = (t_token *[2]){tok, 0}, .token_count = 1, 0};
	return (cmdv_prep(shell, &node));
}


static t_list	*_redirect(struct s_ast_internal *meta,
	t_token **arr,
	size_t addr
)
{
	char			**expanded_filename;
	t_redirect_desc	*redr;
	t_list			*out;
	
	expanded_filename = cheeky_expand(meta->shell, arr[addr + 1]);
	if (ft_arrlen((void *)expanded_filename) > 1 || !expanded_filename[0][0])
	{
		ft_arrclear((void *)expanded_filename, free);
		meta->error = AST_ERR_INVALID_REDIRECT;
		return (0);
	}
	redr = handle_redirect(arr[addr], expanded_filename[0]);
	ft_arrclear((void *)expanded_filename, free);
	out = ft_lstnew(redr);
	if (!redr || !out)
		meta->error = AST_ERR_FATAL;
	if (!out)
		destroy_redirect(redr);
	return (out);
}

static t_list	*_redirectfd(struct s_ast_internal *meta,
	t_token **arr,
	size_t addr
)
{
	t_redirect_desc	*redr;
	t_list			*out;

	(void)addr;
	redr = handle_redirectfd(arr[addr]);
	out = ft_lstnew(redr);
	if (!redr || !out)
		meta->error = AST_ERR_FATAL;
	if (!out)
		destroy_redirect(redr);
	return (out);
}

static t_list	*_heredoc(struct s_ast_internal *meta,
	t_token **arr,
	size_t addr
)
{
	t_redirect_desc	*redr;
	t_list			*out;

	redr = handle_heredoc(meta, arr[addr + 1]->raw);
	out = ft_lstnew(redr);
	if (!out || !redr)
		meta->error = AST_ERR_FATAL;
	if (!out)
		destroy_redirect(redr);
	return (out);
}

int	add_redirect_type(struct s_ast_internal *meta,
	t_token **arr,
	t_astnode *node,
	size_t *inc
)
{
	t_list	*new_node;

	if (!arr[*inc])
		return (0);
	if (arr[*inc]->type == TOK_HEREDOC)
	{
		new_node = _heredoc(meta, arr, *inc);
		inc[0]++;
	}
	else if (arr[*inc]->type == TOK_REDIR_FD)
		new_node = _redirectfd(meta, arr, *inc);
	else
	{
		new_node = _redirect(meta, arr, *inc);
		inc[0]++;
	}
	if (!new_node || !new_node->content)
		return (0); // can assume errors are signaled before this point
	ft_lstadd_back(&node->redirect, new_node);
	return (1);
}
