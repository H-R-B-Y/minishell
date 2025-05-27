/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_consume.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:37 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 17:11:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	post_consume_words(t_minishell *shell,
// 	struct s_ast_internal *meta, t_astnode *node)
// {
// 	size_t	i;
// 	char	*sanitised_heredoc_delim;

// 	i = 0;
// 	while (node->tokens[i])
// 	{
// 		if (node->tokens[i]->type == TOK_HEREDOC)
// 		{
			
// 			i += 1;
// 		}
// 		i++;
// 	}
// }


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
		&& ft_strchr("\1\3\4\5\6\17", meta->tokens[meta->consumed]->type))
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
	// post_consume_words(shell, meta, node);
	return (eaten);
}
