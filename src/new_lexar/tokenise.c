/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 13:28:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_internal(struct s_tokeniserint *meta)
{
	if (meta->parse_stack != 0)
	{
		ft_lstclear(&meta->parse_stack, 0);
		meta->parse_stack = 0;
	}
	if (meta->tokens != 0)
	{
		free_token_list(meta->tokens, free);
		meta->tokens = 0;
	}
}

t_list	*tokenise(t_tokeniserinternal *meta, char *str)
{
	t_list	*out;

	if (!str)
		return (cleanup_internal(meta), (void *)0);
	if (meta->state == PARSE_OK || meta->state == PARSE_ERROR)
	{
		cleanup_internal(meta);
		meta->state = PARSE_OK;
		_begin_parsing(meta, str);
	}
	else if (meta->state == PARSE_CONTINUE)
	{
		_begin_parsing(meta, str + _parse_to_close(meta, str));
		if (ft_lstsize(meta->parse_stack) == 0)
			meta->state = PARSE_OK;
	}
	// parsing has happened
	if (meta->state == PARSE_ERROR)
		return (cleanup_internal(meta), (void *)0);
	if (ft_lstsize(meta->parse_stack) > 0)
	{
		meta->state = PARSE_CONTINUE;
		return ((void *)0);
	}
	out = meta->tokens;
	meta->tokens = 0;
	return (out);
}
