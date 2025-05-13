/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_begin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:50:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 18:44:09 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	_delete_newline(t_list **token)
// {
// 	destroy_token(((t_token *)(*token)->content), free);
// 	free(*token);
// 	*token = 0;
// }

void	_parse_loop_internals(t_tokeniserinternal *meta, t_list *token)
{
	if (!token)
	{
		tokeniser_set_error(meta, ft_strdup("INTERNAL ERROR : null token was generated"));
		return ;
	}
	if (((t_token *)token->content)->type == TOK_END)
	{
		handle_end_token(meta, ft_lstlast(meta->tokens), token);
		return ;
	}
	check_for_parse_errors(meta, ft_lstlast(meta->tokens), token);
	if (meta->state != PARSE_ERROR)
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
		end[1] = skip_token(meta, str, end[0]);
		_parse_loop_internals(meta,
			bin_and_create_token(meta,
			ft_substr(str, end[0], end[1])));
		end[0] += end[1];
	}
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

size_t	_parse_close_paren(t_tokeniserinternal *meta, char *str)
{
	t_list		*next_token;
	t_list		*last_token;
	t_tokentype	type[2];
	size_t		end;

	end = skip_token(meta, str, 0);
	next_token = bin_and_create_token(meta, ft_substr(str, 0, end));
	last_token = ft_lstlast(meta->tokens);
	type[0] = ((t_token *)last_token->content)->type;
	type[1] = ((t_token *)next_token->content)->type;
	if (type[0] == TOK_AFTER || type[0] == TOK_AMP || type[0] == TOK_AND_IF
		|| type[0] == TOK_OR_IF || type[0] == TOK_PIPE)
		return (_parse_loop_internals(meta, next_token), end);
	else if (type[0] == TOK_WORD && (type[1] == TOK_WORD
		|| type[1] == TOK_REDIR_IN || type[1] == TOK_HEREDOC || type[1] == TOK_LPAREN))
		return (append_anon_token(meta, TOK_AFTER, "; "),
			_parse_loop_internals(meta, next_token), end);
	else if (type[0] == TOK_WORD)
		return (_parse_loop_internals(meta, next_token), end);
	else if (type[0] == TOK_LPAREN)
		return (_parse_loop_internals(meta, next_token), end);
	else
		tokeniser_set_error(meta, ft_strdup("PARSE ERROR : No clue what happened here"));
	return (end);
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
	else if (lcont == EXPECT_PAREN)
		return (_parse_close_paren(meta, str));
	return (0);
}
