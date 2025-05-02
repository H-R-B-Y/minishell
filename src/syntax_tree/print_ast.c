/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:27:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/02 18:04:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	_print_indents(char *indent, size_t depth)
{
	while (depth--)
		printf("%s", indent);
}

void	_print_ast_type(t_astnode *head)
{
	static const char *node_types[AST_TYPE_COUNT] = 
	{"NONE", "COMMAND", "AND", "OR", "SEQ", "PIPE", "SUBSHELL"};

	printf("%s", node_types[head->type]);
}
static inline void _print_token_str(t_token *tok)
{
	if (!tok)
		return ;
	printf("%s ", tok->raw);
}

void	_print_ast(t_astnode *head, char *indent, size_t depth)
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

void	print_ast(t_astnode *head, char *indent)
{
	_print_ast(head, indent, 0);
	printf("\n");
}
