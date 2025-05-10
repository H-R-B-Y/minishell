/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 17:50:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_begin_parsing(t_tokeniserinternal *meta, char *str);


/*
I want to rewrite the lexar to better handle inputs

currently there is a small issue with the way we handle errors

when a tokenisation error is happening, we delete the token list, 
then we continue to read lines until we get a valid token list, meaning we re-parse
and re-parse and re-parse again and again until we find a correct list.

this is not good at all, I want to be able to store the state of the tokeniser
and return errors DURING the parsing process so that they can be handled on the
fly.

This means we need to keep track of what is currently being parsed?

I think we might need a stack to store start/end tokens: 
when we encounter a bracket we push to the stack, then we keep parsing until we reach
the end, if there was no close bracket then the error is whatever is on top of the stack?
so quotes and bracket errors are caught here instead of being tested for afterwards?


*/

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

t_list	*tokensise(t_tokeniserinternal *meta, char *str)
{
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
		_begin_parsing(meta, str);
		if (ft_lstsize(meta->parse_stack) == 0)
			meta->state = PARSE_OK;
	}
	// parsing has happened
	if (meta->state == PARSE_ERROR)
		cleanup_internal(meta);
	if (ft_lstsize(meta->parse_stack) > 0)
		meta->state = PARSE_CONTINUE;
	return (meta->tokens);
}
