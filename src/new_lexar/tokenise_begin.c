/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:50:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/10 19:12:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_continuation(t_tokeniserinternal *meta, t_tokentype type);
size_t	token_skip_whitespace(char *str, size_t i);
size_t	skip_token(char *str, size_t i);
t_list	*bin_and_create_token(t_tokeniserinternal *meta, char *raw_token);
void	append_anon_token(t_tokeniserinternal *meta, t_tokentype type, char *str);

// FUCK IDK WHAT TO DO HERE 
/*
if it is a newline after a &&, ||, |, ; delete it.
if it is a newline after in a ( after a WORD then replace it with a SEQ
if it is a newline after a 
*/
void	_delete_newline(t_list **token)
{
	destroy_token(((t_token *)(*token)->content), free);
	free(*token);
	*token = 0;
}

void	_token_check_newline(t_tokeniserinternal *meta, t_list **token)
{
	t_token	*tok;

	if (!meta->tokens)
	{
		_delete_newline(token);
		return ;
	}
	tok = (t_token *)ft_lstlast(meta->tokens)->content;
	if (!meta->parse_stack || LCONT != EXPECT_PAREN || (LCONT == EXPECT_PAREN && (tok->type == TOK_AND_IF || tok->type == TOK_OR_IF
			|| tok->type == TOK_AFTER || tok->type == TOK_AMP)))
	{
			_delete_newline(token);
	}
	else
	{
		tok = (t_token *)(*token)->content;
		tok->type = TOK_AFTER;
		free(tok->raw);
		free(tok->trimmed);
		tok->raw = ft_strdup("; ");
		tok->trimmed = ft_strdup(";");
	}
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
	if (PTRTOE ((t_token *)token->content)->type == TOK_NEWLINE)
		_token_check_newline(meta, &token);
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
		// end[0] += token_skip_whitespace(str, end[0]);// skip whitespace but not escaped whitespace
		if (!str[end[0]])
			return ;
		if (end[0] == '\n' && ft_lstsize(meta->parse_stack) == 0)
			return ;
		end[1] = skip_token(str, end[0]);
		_parse_loop_internals(meta,
			bin_and_create_token(meta,
			ft_substr(str, end[0], end[1])));
		end[0] += end[1];
	}
	if (meta->tokens && ((t_token *)ft_lstlast(meta->tokens)->content)->type == TOK_WORD && meta->parse_stack && LCONT == EXPECT_PAREN)
		append_anon_token(meta, TOK_AFTER, ft_strdup(";"));
}
