/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_printing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:20:41 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:39:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

const char	*token_type_to_string(t_tokentype type)
{
	static const char	*types[TOK_COUNT] = {
		"None", "Word", "Pipe", "Redirect out (>)",
		"Redirect append (>>)", "Redirect in (<)", "Heredoc",
		"After (;)", "And", "Or", "Open parenthesis",
		"Close parenthesis", "Disown (&)", "End of input",
		"Incomplete string", "Redirect to fd"
	};

	return (types[type]);
}

void	print_token_type(t_tokentype type)
{
	printf("%s", token_type_to_string(type));
}

void	print_token(t_token *token, int column_width)
{
	printf("%-*s;  %*s\n", column_width, token_type_to_string(token->type),
		column_width, token->raw);
}

void	print_token_list(t_list *list)
{
	t_list	*next;

	next = list;
	while (next)
	{
		print_token(next->content, 25);
		next = next->next;
	}
}
