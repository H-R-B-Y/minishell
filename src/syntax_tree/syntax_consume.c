/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_consume.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/17 18:23:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ast_consume_words(struct s_ast_internal *meta, t_astnode *node)
{
	size_t	consumed;
	size_t	i;

	consumed = 0;
	while (meta->tokens[meta->consumed]
		&& meta->tokens[meta->consumed + consumed]
		&& (meta->tokens[meta->consumed + consumed]->type == TOK_WORD
		|| meta->tokens[meta->consumed + consumed]->type == TOK_HEREDOC
		|| meta->tokens[meta->consumed + consumed]->type == TOK_REDIR_IN
		|| meta->tokens[meta->consumed + consumed]->type == TOK_REDIR_OUT
		|| meta->tokens[meta->consumed + consumed]->type == TOK_REDIR_FD
		|| meta->tokens[meta->consumed + consumed]->type == TOK_REDIR_APPEND))
		consumed++;
	node->tokens = ft_calloc(consumed + 1, sizeof(t_token *));
	i = 0;
	while (i < consumed)
	{
		node->tokens[i] = meta->tokens[meta->consumed + i];
		i++;
	}
	node->token_count = consumed;
	return (consumed);
}
