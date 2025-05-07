/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanse_validate_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:52:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/07 10:56:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: help
int	quotes_are_matched(char *str)
{
	char	quote;

	if (!str || !*str)
		return (1);
	if (!(*str == '"' || *str == '\''))
		return (1);
	quote = *str;
	if (ft_strlen(str) > 1 && str[ft_strlen(str) - 1] == quote
		&& (str[ft_strlen(str) - 2] != '\\' || quote == '\'')) //TODO: double quote can be escaped
		return (1);
	return (0);
}

char	*remove_quotes_from_string(char *str)
{
	char	*str2;

	str2 = ft_substr(str, 1, ft_strlen(str) - 2);
	return (str2);
}

void	cleanup_word(t_token *token)
{
	char	*str;

	str = 0;
	if (!token || token->type != TOK_WORD)
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
	if (tok->type == TOK_RPAREN) // TODO: this does not hadle the case )(
		(*parenthesis)--;
	else if (tok->type == TOK_LPAREN)
		(*parenthesis)++;
	else if (tok->type == TOK_WORD)
	{
		if (*tok->raw == '"' || *tok->raw == '\'')
			if (!quotes_are_matched(tok->raw))
				return (UNCLOSED_SINGLEQUOTE + (1 * (*tok->raw == '"')));
		cleanup_word(tok);
	}
	else if (tok->type == TOK_HEREDOC)
	{
		if (!node->next || ((t_token *)node->next->content)->type != TOK_WORD)
			return (HEREDOC_WITHOUT_WORD);
		else
			((t_token *)node->next->content)->heredoc_deliminator = 1;
	}
	return (TOK_ERR_NONE);
}

// TODO: we should return why the tokens are invalid:
// unclosed quotes means go back to readline to find the end of the sequence 
// unclosed parenthesis means go back to readline to find the end of the sequence
// this means we should keep appending tokens from the newline until the tokens are valid
t_tokerr	cleanse_validate_tokens(t_list *tokens)
{
	t_list		*node;
	t_token		*tok;
	long int	parenthesis;
	t_tokerr	err;

	parenthesis = 0;
	node = tokens;
	err = TOK_ERR_NONE;
	while (node && !err && parenthesis >= 0)
	{
		tok = ((t_token *)node->content);
		err = _handle_token(node, tok, &parenthesis);
		node = node->next;
		if (err || parenthesis < 0)
			break ;
	}
	if (err)
		return (err);
	else if (parenthesis != 0)
		return (UNCLOSED_PARENTHESIS);
	else
		return (TOK_ERR_NONE);
}
