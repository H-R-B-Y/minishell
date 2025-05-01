/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanse_validate_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:52:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 19:25:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: help
int	quotes_are_matched(char *str)
{
	char quote;

	if (!str || !*str)
		return (1);
	if (!(*str == '"' || *str == '\''))
		return (1);
	quote = *str;
	if (str[ft_strlen(str) - 1] == quote)//TODO: double quote can be escaped
		return (1);
	return (0);
}

char	*remove_quotes_from_string(char *str)
{
	char *str2;

	str2 = ft_substr(str, 1, ft_strlen(str) - 2);
	return (str2);
}

void	cleanup_word(t_token *token)
{
	char *str;
	
	str = 0;
	if (!token || token->type != WORD)
		return ;
	if (*(token->raw) == '\'')
		token->variables_expanded = 1;
	if (*(token->raw) == '\'' || *(token->raw) == '"')
		str = remove_quotes_from_string(token->raw);
	if (!str)
		str = ft_strdup(token->raw);
	token->text = str;
}

static int	_handle_token(t_list *node, t_token *tok, long int *parenthesis)
{
	int	invalid;

	invalid = 0;
	if (tok->type == RPAREN) // TODO: this does not hadle the case )(
		(*parenthesis)--;
	else if (tok->type == LPAREN)
		(*parenthesis)++;
	else if (tok->type == WORD)
	{
		if (*tok->raw == '"' || *tok->raw == '\'')
			invalid += !quotes_are_matched(tok->raw);
		if (!invalid)
			cleanup_word(tok);
	}
	else if (tok->type == HEREDOC)
	{
		if (((t_token *)node->next->content)->type != WORD)
			invalid += 1;
		else 
			((t_token *)node->next->content)->heredoc_deliminator = 1;
	}
	return	(invalid);
}

int	cleanse_validate_tokens(t_list *tokens)
{
	t_list		*node;
	t_token		*tok;
	int			invalid;
	long int	parenthesis;

	parenthesis = 0;
	node = tokens;
	invalid = 0;
	while (node && !invalid)
	{
		tok = ((t_token *)node->content);
		invalid += _handle_token(node, tok, &parenthesis);
		node = node->next;
	}
	if (invalid || parenthesis != 0)
		return (0);
	return (1);
}

