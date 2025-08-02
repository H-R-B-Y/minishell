/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:25:05 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 18:38:00 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// static int	_add_redirects(struct s_ast_internal *meta,
// 	t_astnode *node,
// 	size_t *i,marvin
// 	t_token ***new_tokenv
// )
// {
// 	if (node->tokens[i[0]]->type == TOK_HEREDOC)
// 	{
// 		ft_lstadd_back(&node->redirect,
// 			ft_lstnew(handle_heredoc(meta, node->tokens[i[0] + 1]->raw)));
// 		i[0]++;
// 	}
// 	else if (ft_strchr("\4\5\3", node->tokens[i[0]]->type))
// 	{
// 		ft_lstadd_back(&node->redirect,
// 			ft_lstnew(handle_redirect(node->tokens[i[0]],
// 					node->tokens[i[0] + 1])));
// 		i[0]++;
// 	}
// 	else if (node->tokens[i[0]]->type == TOK_REDIR_FD)
// 		ft_lstadd_back(&node->redirect,
// 			ft_lstnew(handle_redirectfd(node->tokens[i[0]])));
// 	else
// 		(*new_tokenv)[i[1]++] = node->tokens[i[0]];
// 	return (1);
// }

static t_redirect_desc	*_redirect(struct s_ast_internal *meta,
	t_astnode *node,
	size_t addr
)
{
	char			**expanded_filename;
	t_redirect_desc	*out;

	expanded_filename = expand_and_split(meta->shell,
		node->tokens[addr + 1]->raw, 3);
	if (ft_arrlen((void *)expanded_filename) > 1)
	{
		meta->error = AST_ERR_INVALID_REDIRECT;
		return (0);
	}
	out = handle_redirect(node->tokens[addr], expanded_filename[0]);
	if (!out)
		meta->error = AST_ERR_FATAL;
	return (out);
}

int	add_redirect_type(struct s_ast_internal *meta,
	t_token **arr,
	t_astnode *node,
	size_t *inc
)
{
	t_list	*new_node;

	if (ft_strchr("\4\5\3\6", arr[*inc]->type))
	{
		if (arr[*inc]->type == TOK_HEREDOC)
			new_node = ft_lstnew(
				handle_heredoc(meta, arr[*inc + 1]->raw));
		else
			new_node = ft_lstnew(_redirect(meta, node, *inc));
		*inc = *inc + 1;
	}
	else if (arr[*inc]->type == TOK_REDIR_FD)
		new_node = ft_lstnew(handle_redirectfd(arr[*inc]));
	if (!new_node || !new_node->content)
		return (-1);
	ft_lstadd_back(&node->redirect, new_node);
	return (1);
}
