/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   produce_syntax_tree.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:20:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:26:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_astnode	*produce_ast(t_token **tokens, size_t count)
{
	struct s_ast_internal	meta;
	t_astnode				*head;

	meta.tokens = tokens;
	meta.count = count;
	meta.consumed = 0;
	meta.left_node = 0;
	meta.right_node = 0;
	head = ast_parse_seperators(&meta);
	return (head);
}
