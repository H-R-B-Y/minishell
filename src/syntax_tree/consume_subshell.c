/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:46:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/21 17:52:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ast_subcommand_redirects(struct s_ast_internal *meta, t_astnode *node)
{
	while(meta->tokens[meta->consumed] && 
		ft_strchr("\3\4\5\6\17", meta->tokens[meta->consumed]->type))
	{
		if (meta->tokens[meta->consumed]->type == TOK_HEREDOC)
		{
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_heredoc(meta, meta->tokens[meta->consumed + 1]->raw,
					meta->tokens[meta->consumed])));
			meta->consumed++;
		}
		else if (meta->tokens[meta->consumed]->type == TOK_REDIR_FD)
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_redirectfd(meta->tokens[meta->consumed])));
		else
		{
			ft_lstadd_back(&node->redirect,
				ft_lstnew(handle_redirect(meta->tokens[meta->consumed],
					meta->tokens[meta->consumed + 1])));
			meta->consumed++;
		}
		meta->consumed++;
	}
	if (meta->tokens[meta->consumed]
		&& ft_strchr("\1\12", meta->tokens[meta->consumed]->type))
		meta->error = AST_ERR_SYNTAX;
}

t_astnode	*ast_parse_subcommand(struct s_ast_internal *meta)
{
	t_astnode	*me;

	me = create_ast_node(AST_SUBSHELL, 0, 0, 0);
	if (!me)
		meta->error = AST_ERR_FATAL;
	meta->consumed++;
	me->left_node = ast_parse_seperators(meta);
	if ((meta->tokens[meta->consumed]
			&& meta->tokens[meta->consumed]->type != TOK_RPAREN)
		|| !meta->tokens[meta->consumed])
	{
		meta->error = AST_ERR_SYNTAX;
		destroy_ast_node(me);
		return (0);
	}
	meta->consumed++;
	ast_subcommand_redirects(meta, me);
	return (me);
}
