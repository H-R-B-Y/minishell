/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 12:13:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	skip_quoted(char *str, size_t i)
{
	size_t	start;
	char	quote;

	quote = str[i];
	start = i;
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i - start);
}

size_t	skip_token(char *str, size_t i)
{
	size_t	start;

	start = i;
	if (str[i] == '\'' || str[i] == '"')
		i += skip_quoted(str, i);
	else if (str[i] == '<' || str[i] == '>')
		if (++i && str[i] == str[i - 1])
			i += 1;
	else if (str[i] == '|' || str[i] == '(' || str[i] == ')')
		i++;
	else
	{
		while (str[i] && !ft_iswhitespace(str[i]) && !isoperator(str[i]))
		{
			if (str[i] == '\'' || str[i] == '"')
				i += skip_quoted(str, i);
			else
				i++;
		}
	}
	return (i - start);
}

size_t	skip_whitespace(char *str, size_t i)
{
	size_t	start;

	start = i;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (i - start);
}

t_list *tokenise(char *str)
{
	char	*raw_token;
	t_list	*tokens[2];
	size_t	token_start;
	size_t	token_end;

	if (!str || !*str)
		return ((void *)0);
	token_start = 0;
	ft_memset(tokens, 0, sizeof(size_t) * 2);
	while (str[token_start])
	{
		token_start += skip_whitespace(str, token_start);
		if (str[token_start])
		{
			token_end = skip_token(str, token_start);
			tokens[1] = bin_and_create_token(ft_substr(str, token_start, token_end));
			if (!tokens[1])
				break ;
			ft_lstadd_back(&tokens[0], tokens[1]);
			token_start += token_end;
		}
	}
	if (tokens[1] == 0 && tokens[0])
		return (cleanup_tokens(tokens[0], free));
	return (tokens[0]);
}
