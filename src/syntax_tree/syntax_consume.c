/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_consume.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 13:51:22 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	post_consume_words(t_minishell *shell,
	struct s_ast_internal *meta, t_astnode *node)
{
	size_t	i[2];
	t_token	**new_tokenv;

	i[0] = 0;
	i[1] = 0;
	(void)meta;
	new_tokenv = ft_calloc(ft_arrlen((void *)node->tokens) + 1, sizeof(void *));
	while (node->tokens[i[0]])
	{
		if (node->tokens[i[0]]->type == TOK_HEREDOC)
		{
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_heredoc(shell, node->tokens[i[0] + 1]->raw)));
			i[0] += 2;
			continue ;
		}
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
size_t	ast_consume_words(t_minishell *shell,
	struct s_ast_internal *meta, t_astnode *node)
{
	size_t	eaten;
	size_t	i;

	(void)shell;
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
	post_consume_words(shell, meta, node);
	return (eaten);
}
