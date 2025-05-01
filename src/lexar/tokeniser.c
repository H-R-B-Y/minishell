/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 19:20:03 by hbreeze          ###   ########.fr       */
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
	while (str[i] && (str[i] != quote
		|| (str[i] == quote && i > 1)))//TODO: double quote can be escaped
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
	else if (str[i] == '<' || str[i] == '>' || str[i] == '&' || str[i] == '|')
	{
		if (++i && str[i] == str[i - 1])
			i++;
	}
	else if (str[i] == '(' || str[i] == ')' || str[i] == ';')
		i++;
	else
	{
		while (str[i] && !ft_iswhitespace(str[i]) && !isoperator(str[i]))
		{
			if (str[i] == '\'' || str[i] == '"')
				i += skip_quoted(str, i);
			else if (str[i] == '\\' && (ft_iswhitespace(str[i+1]) || isoperator(str[i+1]) || str[i+1] == '\\' || str[i+1] == '"' || str[i+1] == '\''))
				i += 2;
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

int	cleanup_tokens(t_list *tokens, void (*del_raw)(void *))
{
	t_list	*head;
	t_list	*prev;

	prev = tokens;
	head = tokens->next;
	while (prev)
	{
		destroy_token(prev->content, del_raw);
		free(prev);
		prev = head;
		head = head->next;
	}
	return (0);
}

t_list *tokenise(char *str)
{
	t_list	*tokens[2];
	size_t	ends[2];

	if (!str || !*str)
		return ((void *)0);
	ends[0] = 0;
	ft_memset(tokens, 0, sizeof(size_t) * 2);
	while (str[ends[0]])
	{
		ends[0] += skip_whitespace(str, ends[0]);
		if (str[ends[0]])
		{
			ends[1] = skip_token(str, ends[0]);
			tokens[1] = bin_and_create_token(ft_substr(str, ends[0], ends[1]));
			if (!tokens[1])
				break ;
			ft_lstadd_back(&tokens[0], tokens[1]);
			ends[0] += ends[1];
		}
	}
	if (tokens[1] == 0 && tokens[0])
		return (cleanup_tokens(tokens[0], &free), (void *)0);
	return (tokens[0]);
}
