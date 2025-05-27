/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:36:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:39:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

t_token	*create_token(t_tokentype type, char *raw_token)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return ((void *)0);
	ft_bzero(tok, sizeof(t_token));
	tok->raw = raw_token;
	tok->type = type;
	return (tok);
}

void	destroy_token(t_token *token, void (*del_raw)(void *))
{
	if (!token)
		return ;
	if (token->raw && del_raw)
		del_raw(token->raw);
	free(token);
}

void	free_token_list(t_list *list, void (*del_raw)(void *))
{
	t_list	*start;
	t_list	*next;

	if (!list || !list->content)
		return ;
	start = list;
	while (start)
	{
		next = start->next;
		if (start->content)
			destroy_token(start->content, del_raw);
		free(start);
		start = next;
	}
}

void	free_token_vector(t_token **vec, void (*del_raw)(void *))
{
	size_t	i;

	if (!vec || !*vec)
		return ;
	i = 0;
	while (vec[i])
		destroy_token(vec[i++], del_raw);
}

void	append_anon_token(t_fsmdata *fsm, t_tokentype type, char *str)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	*tok = (t_token){.heredoc_delim = 0, .raw = str, .type = type};
	ft_lstadd_back(&fsm->tokens, ft_lstnew(tok));
}
