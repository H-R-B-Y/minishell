/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:51:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

const char	*token_type_to_string(t_tokentype type)
{
	static const char	*types[TOK_COUNT] = {
		"None", "Word", "Pipe", "Redirect out (>)",
		"Redirect append (>>)", "Redirect in (<)", "Heredoc",
		"After (;)", "And", "Or", "Open parenthesis",
		"Close parenthesis", "Disown (&)", "End of input"
	};

	return (types[type]);
}

const char	*token_err_type_to_string(t_tokerr err)
{
	static const char	*errors[TOKEN_ERROR_COUNT] = {
		"TOK_ERR_NONE",
		"UNCLOSED_SINGLEQUOTE",
		"UNCLOSED_DOUBLEQUOTE",
		"UNCLOSED_PARENTHESIS",
		"HEREDOC_WITHOUT_WORD",
	};

	return (errors[err]);
}

void	print_token_type(t_tokentype type)
{
	printf("%s", token_type_to_string(type));
}

void	print_token_error(t_tokerr err)
{
	printf("%s", token_err_type_to_string(err));
}

void	print_token(t_token *token, int column_width)
{
	printf("%-*s;  %*s; %*s\n", column_width, token_type_to_string(token->type),
		column_width, token->raw, column_width, token->text);
}
