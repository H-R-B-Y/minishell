/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:46:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 15:09:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	add_redirect_type(struct s_ast_internal *meta, t_token **arr,
						t_astnode *node, size_t *inc);

static int	post_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	size_t	i[2];
	t_token	**new_tokenv;

	(void)meta;
	ft_bzero(i, sizeof(size_t) * 2);
	new_tokenv = ft_calloc(ft_arrlen((void *)node->tokens) + 1, sizeof(void *));
	while (node->tokens[i[0]])
	{
		if (ft_strchr("\3\4\5\6\17", node->tokens[i[0]]->type))
		{
			if (add_redirect_type(meta, node->tokens, node, &i[0]) < 0)
				return (free(new_tokenv), 0);
		}
		else
			new_tokenv[i[1]++] = node->tokens[i[0]];
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
	// append_tokenv_to_history_item(shell, &shell->rldata, node->tokens);
	node->token_count = ft_arrlen((void *)node->tokens);
	return (eaten);
}
