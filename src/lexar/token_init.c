/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/07 11:01:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(t_tokentype type, char *raw_token)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	ft_bzero(tok, sizeof(t_token));
	tok->raw = raw_token;
	tok->type = type;
	return (tok);
}

void	destroy_token(t_token *token, void (*del_raw)(void *), void (*del_str)(void *))
{
	if (!token)
		return ;
	if (token->raw && del_raw)
		del_raw(token->raw);
	if (token->text && del_str)
		del_str(token->text);
	free(token);
}

void	free_token_list(t_list *list, void (*del_raw)(void *), void (*del_str)(void *))
{
	t_list	*start;
	t_list	*next;

	if (!list || !list->content)
		return ;
	start = list;
	next = list->next;
	while (start)
	{
		if (start->content)
			destroy_token(start->content, del_raw, del_str);
		free(start);
		start = next;
		if (start)
			next = next->next;
	}
}

void	free_token_vector(t_token **vec, void (*del_raw)(void *), void (*del_str)(void *))
{
	size_t	i;

	if (!vec || !*vec)
		return ;
	i = 0;
	while (vec[i])
	{
		destroy_token(vec[i], del_raw, del_str);
		i++;
	}
}
