/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:50:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 13:28:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_delete_newline(t_list **token)
{
	destroy_token(((t_token *)(*token)->content), free);
	free(*token);
	*token = 0;
}

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

	if (!str || !*str)
		return ;
	end[0] = 0;
	while(str[end[0]] && meta->state != PARSE_ERROR)
	{
		if (!str[end[0]])
			return ;
		if (end[0] == '\n' && ft_lstsize(meta->parse_stack) == 0)
			return ;
		end[1] = skip_token(meta, str, end[0]);
		_parse_loop_internals(meta,
			bin_and_create_token(meta,
			ft_substr(str, end[0], end[1])));
		end[0] += end[1];
	}
	// This should be done when appending the next lines tokens
	// if (meta->tokens
	// 	&& ((t_token *)ft_lstlast(meta->tokens)->content)->type == TOK_WORD
	// 	&& meta->parse_stack && LCONT == EXPECT_PAREN)
	// 	append_anon_token(meta, TOK_AFTER, ft_strdup(";"));
}

size_t	_parse_close_quote(t_tokeniserinternal *meta, char *str,
	t_token *amend, char quote)
{
	size_t	ends[2];
	char	*temp[2];

	ends[0] = 0;
	ends[1] = skip_word(meta, str, ends[0], quote);
	temp[0] = ft_substr(str, ends[0], ends[1]);
	temp[1] = str_join_with_sep(amend->raw, temp[0], "\n");
	free(amend->raw);
	free(amend->trimmed);
	amend->raw = temp[1];
	amend->trimmed =  ft_strtrim(amend->raw, " \t\v\b\r\f");
	free(temp[0]);
	return (ends[1]);
}

size_t	_parse_to_close(t_tokeniserinternal *meta, char *str)
{
	t_tokcont	lcont;

	if (!meta->parse_stack || !meta->tokens)
		return (0);
	lcont = LCONT;
	if (lcont == EXPECT_QUOTE || lcont == EXPECT_DQUOTE)
		return (_parse_close_quote(meta, str,
			(t_token *)(ft_lstlast(meta->tokens)->content),
			('\'' - (5 * (lcont == EXPECT_DQUOTE)))));
	// if the next token is a word or redirect insert a sequence,
	// if the token is not a word or redirect it MUST be 
	// a parenthesis
	if (lcont == EXPECT_PAREN) 
		return (printf("expecting parenthesis not finished\n"), 0);
	return (0);
}
