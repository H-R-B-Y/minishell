/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 11:23:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	skip_token(char *str, size_t i);

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

t_list	*tokenise(char *str)
{
	t_list	*tokens[2];
	size_t	ends[2];

	if (!str || !*str)
		return ((void *)0);
	ends[0] = 0;
	ft_memset(tokens, 0, sizeof(t_list *) * 2);
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
