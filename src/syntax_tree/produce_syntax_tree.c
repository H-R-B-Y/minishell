/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   produce_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 15:13:22 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_astnode	*produce_ast(t_minishell *shell, t_token **tokens, size_t count)
{
	struct s_ast_internal	meta;
	t_astnode				*head;

	if (!tokens || !*tokens || !count)
		return ((void *)0);
	meta.tokens = tokens;
	meta.count = count;
	meta.consumed = 0;
	meta.left_node = 0;
	meta.right_node = 0;
	head = ast_parse_seperators(&meta);
	return (head);
}
