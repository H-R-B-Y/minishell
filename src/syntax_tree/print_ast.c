/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:27:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/23 14:37:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	_print_indents(const char *indent, size_t depth)
{
	while (depth--)
		printf("%s", indent);
}

static void	_print_ast_type(const t_astnode *head)
{
	static const char	*node_types[AST_TYPE_COUNT]
		= {"NONE", "COMMAND", "AND", "OR", "SEQ", "PIPE", "SUBSHELL"};

	printf("%s", node_types[head->type]);
}

static inline void	_print_token_str(const t_token *tok)
{
	if (!tok)
		return ;
	printf("%s ", tok->raw);
}

static void	_print_ast(const t_astnode *head, const char *indent, size_t depth)
{
	if (!head)
		return ;
	_print_indents(indent, depth);
	if (head->type != AST_COMMAND)
		_print_ast_type(head);
	else
		ft_arriter((void *)head->tokens, (void *)_print_token_str);
	printf("\n");
	_print_ast(head->left_node, indent, depth + 1);
	_print_ast(head->right_node, indent, depth + 1);
}

void	print_ast(const t_astnode *head, const char *indent)
{
	_print_ast(head, indent, 0);
	printf("\n");
}
