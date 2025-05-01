/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 11:38:21 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*token_type_to_string(t_tokentype type)
{
	const static char	*types[TOKEN_COUNT] = {
		"None", "Word", "Pipe", "Redirect out (>)",
		"Redirect append (>>)", "Redirect in (<)", "Heredoc",
		"After (;)", "And", "Or", "Open parenthesis",
		"Close parenthesis", "Disown (&)", "End of input"
	};
	
	return (types[type]);
}

void	*print_token_type(t_tokentype type)
{
	printf("%s", token_type_to_string(type));
}

void	print_token(t_token *token, size_t column_width)
{
	printf("%-*s;  %s", column_width,  token_type_to_string(token->type), token->raw);
}

