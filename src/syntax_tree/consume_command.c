/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:46:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 19:11:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	_add_redirects(struct s_ast_internal *meta,
	t_astnode *node,
	size_t *i,
	t_token ***new_tokenv
)
{
	if (node->tokens[i[0]]->type == TOK_HEREDOC)
	{
		ft_lstadd_back(&node->redirect,
			ft_lstnew(handle_heredoc(meta, node->tokens[i[0] + 1]->raw,
					node->tokens[i[0]])));
		i[0]++;
	}
	else if (ft_strchr("\4\5\3", node->tokens[i[0]]->type))
	{
		ft_lstadd_back(&node->redirect,
			ft_lstnew(handle_redirect(node->tokens[i[0]],
					node->tokens[i[0] + 1])));
		i[0]++;
	}
	else if (node->tokens[i[0]]->type == TOK_REDIR_FD)
		ft_lstadd_back(&node->redirect,
			ft_lstnew(handle_redirectfd(node->tokens[i[0]])));
	else
		(*new_tokenv)[i[1]++] = node->tokens[i[0]];
	return (1);
}

static int	post_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	size_t	i[2];
	t_token	**new_tokenv;

	(void)meta;
	ft_bzero(i, sizeof(size_t) * 2);
	new_tokenv = ft_calloc(ft_arrlen((void *)node->tokens) + 1, sizeof(void *));
	while (node->tokens[i[0]])
	{
		if (_add_redirects(meta, node, i, &new_tokenv) < 0)
			return (free(new_tokenv), 0);
		i[0]++;
	}
	free(node->tokens);
	node->tokens = new_tokenv;
	return (1);
}

ssize_t	ast_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	ssize_t	eaten;
	ssize_t	i;

	eaten = 0;
	while (_continue_parsing(meta) && meta->tokens[meta->consumed + eaten]
		&& ft_strchr("\1\3\4\5\6\17",
			meta->tokens[meta->consumed + eaten]->type))
		eaten++;
	node->tokens = ft_calloc(eaten + 1, sizeof(t_token *));
	if (!node->tokens)
		return (-1);
	node->token_arr_freeable = 1;
	i = 0;
	while (i < eaten)
	{
		node->tokens[i] = meta->tokens[meta->consumed + i];
		i++;
	}
	if (!post_consume_words(meta, node))
		return (-1);
	node->token_count = ft_arrlen((void *)node->tokens);
	return (eaten);
}
