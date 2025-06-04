/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/04 18:17:20 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	post_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	size_t	i[2];
	t_token	**new_tokenv;

	(void)meta;
	ft_bzero(i, sizeof(size_t) * 2);
	new_tokenv = ft_calloc(ft_arrlen((void *)node->tokens) + 1, sizeof(void *));
	while (node->tokens[i[0]])
	{
		if (node->tokens[i[0]]->type == TOK_HEREDOC)
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_heredoc(meta, node->tokens[++i[0]]->raw)));
		// TOK_REDIR_APPEND && TOK_REDIR_FD && TOK_REDIR_IN && TOK_REDIR_OUT
		else if (ft_strchr("\4\5\3", node->tokens[i[0]]->type))
		{
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_redirect(node->tokens[i[0]], node->tokens[i[0] +1 ])));
			i[0]++;
		}
		else if (node->tokens[i[0]]->type == TOK_REDIR_FD)
			ft_lstadd_back(&node->redirect, ft_lstnew(handle_redirectfd(node->tokens[i[0]])));
		else
			new_tokenv[i[1]++] = node->tokens[i[0]];
		i[0]++;
	}
	free(node->tokens);
	node->tokens = new_tokenv;
}

// && (meta->tokens[meta->consumed + eaten]->type == TOK_WORD // 1
// || meta->tokens[meta->consumed + eaten]->type == TOK_REDIR_OUT // 3
// || meta->tokens[meta->consumed + eaten]->type == TOK_REDIR_APPEND)) // 4
// || meta->tokens[meta->consumed + eaten]->type == TOK_REDIR_IN // 5
// || meta->tokens[meta->consumed + eaten]->type == TOK_HEREDOC // 6
// || meta->tokens[meta->consumed + eaten]->type == TOK_REDIR_FD // 17
size_t	ast_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	size_t	eaten;
	size_t	i;

	eaten = 0;
	while (meta->tokens[meta->consumed] && meta->tokens[meta->consumed + eaten]
		&& ft_strchr("\1\3\4\5\6\17", meta->tokens[meta->consumed + eaten]->type))
		eaten++;
	node->tokens = ft_calloc(eaten + 1, sizeof(t_token *));
	node->token_arr_freeable = 1;
	i = 0;
	while (i < eaten)
	{
		node->tokens[i] = meta->tokens[meta->consumed + i];
		i++;
	}
	node->token_count = eaten;
	post_consume_words(meta, node);
	return (eaten);
}
