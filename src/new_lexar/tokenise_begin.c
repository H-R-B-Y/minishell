/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:50:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 15:58:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_continuation(t_tokeniserinternal *meta, t_tokentype type);
size_t	token_skip_whitespace(char *str, size_t i);

void	_parse_loop_internals(t_tokeniserinternal *meta, t_list *token)
{
	if (!token)
	{
		meta->state = PARSE_ERROR;
		return ;
	}
	update_continuation(meta, ((t_token *)token->content)->type);
	if (meta->state == PARSE_ERROR)
	{
		destroy_token(token->content, free);
		free(token);
		return ;
	}
	ft_lstadd_back(&meta->tokens, token);
}

void	_begin_parsing(t_tokeniserinternal *meta, char *str)
{
	size_t	end[2];
	t_list	*token;

	if (!str || !*str)
		return ;
	end[0] = 0;
	while(str[end[0]] && meta->state != PARSE_ERROR)
	{
		end[0] += token_skip_whitespace(str, end[0]);// skip whitespace but not escaped whitespace
		if (!str[end[0]])
			continue ;
		end[1] = skip_token(str, end[0]);
		_parse_loop_internals(meta, bin_and_create_token(meta,
			ft_substr(str, end[0], end[1])));
		end[0] += end[1];
	}
}
