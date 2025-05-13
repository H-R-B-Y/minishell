/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:50:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 11:31:49 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_continuation(t_tokeniserinternal *meta, t_tokentype type);
size_t	token_skip_whitespace(char *str, size_t i);
size_t	skip_token(t_tokeniserinternal *meta, char *str, size_t i);
t_list	*bin_and_create_token(t_tokeniserinternal *meta, char *raw_token);
void	append_anon_token(t_tokeniserinternal *meta, t_tokentype type, char *str);
size_t	skip_quoted(char *str, size_t i, char quote);
size_t	skip_word(t_tokeniserinternal *meta, char *str, size_t i, char quote);

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
	if (meta->tokens
		&& ((t_token *)ft_lstlast(meta->tokens)->content)->type == TOK_WORD
		&& meta->parse_stack && LCONT == EXPECT_PAREN)
		append_anon_token(meta, TOK_AFTER, ft_strdup(";"));
}

size_t	_skip_quoted_internal(t_tokeniserinternal *meta, char *str, size_t i, char quote);
int	quote_closed(char *str, size_t i, char quote);

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



size_t	_parse_escaped_newline(t_tokeniserinternal *meta, char *str,
	t_token *amend)
{
	size_t	ends[2];
	// char	*temp[2];
	
	(void)amend;
	ends[0] = 0;
	ends[1] = skip_word(meta, str, ends[0], 0);
	return (0);
}

size_t	_parse_to_close(t_tokeniserinternal *meta, char *str)
{
	t_token	*amend;
	t_tokcont	lcont;

	if (!meta->parse_stack || !meta->tokens)
		return (0);
	lcont = LCONT;
	if (lcont != EXPECT_QUOTE && lcont != EXPECT_DQUOTE
		&& lcont != ESCAPED_NEWLINE)
		return (0);
	amend = (t_token *)(ft_lstlast(meta->tokens)->content);
	if (lcont == EXPECT_DQUOTE || lcont == EXPECT_QUOTE)
		return (_parse_close_quote(meta, str, amend,
			('\'' - (5 * (lcont == EXPECT_DQUOTE)))));
	else
		return (_parse_escaped_newline(meta, str, amend));
}
