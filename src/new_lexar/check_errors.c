/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:10:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/13 18:33:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_end_token(t_tokeniserinternal *meta, t_list *last_token, t_list *next_token)
{
	t_token		*token[2];
	char		*tmp;

	(void)meta;
	if (last_token == 0)
	{
		destroy_token(next_token->content, free);
		free(next_token);
		return ;
	}
	token[0] = (t_token *)last_token->content;
	token[1] = (t_token *)next_token->content;
	tmp = ft_strjoin(token[0]->raw, token[1]->raw);
	free(token[0]->raw);
	free(token[1]->raw);
	token[0]->raw = tmp;
	destroy_token(next_token->content, 0);
	free(next_token);
	return ;
}

/*
what parse errors can occur:

two symbols in a row

heredoc without word

???
*/

void	check_single_error(t_tokeniserinternal *meta, t_list *next_token)
{
	t_token		*token;
	t_tokentype	type;

	token = (t_token *)next_token->content;
	type = token->type;
	if (type == TOK_AFTER || type == TOK_AMP || type == TOK_AND_IF
		|| type == TOK_OR_IF || type == TOK_REDIR_OUT || type == TOK_RPAREN
		|| type == TOK_REDIR_APPEND || type == TOK_PIPE)
		tokeniser_set_error(meta, str_join_with_sep("PARSE ERROR : "," : cannot be parsed",  token->raw));
	return ;
}


void	check_for_parse_errors(t_tokeniserinternal *meta, t_list *last_token, t_list *next_token)
{
	t_token		*token[2];
	t_tokentype	type[2];

	if (!last_token)
	{
		check_single_error(meta, next_token);
		return ;
	}
	token[0] = (t_token *)last_token->content;
	token[1] = (t_token *)next_token->content;
	type[0] = token[0]->type;
	type[1] = token[1]->type;
	if ((type[0] == TOK_HEREDOC || type[0] == TOK_REDIR_APPEND || type[0] == TOK_REDIR_OUT) && (type[1] != TOK_WORD))
			tokeniser_set_error(meta, str_vec_join((char *[5]){"ERROR : ", token[1]->raw, " cannot append ", token[0]->raw, 0}));
	else if ((type[0] == TOK_AND_IF || type[0] == TOK_OR_IF || type[0] == TOK_AMP || type[0] == TOK_AFTER) && !(type[1] == TOK_WORD || type[1] == TOK_LPAREN || type[1] == TOK_REDIR_IN || type[1] == TOK_HEREDOC))
			tokeniser_set_error(meta, str_vec_join((char *[5]){"ERROR : ", token[1]->raw, " cannot append ", token[0]->raw, 0}));
	else if (type[0] == TOK_REDIR_IN && type[1] != TOK_WORD)
			tokeniser_set_error(meta, str_vec_join((char *[5]){"ERROR : ", token[1]->raw, " cannot append ", token[0]->raw, 0}));
	else if (type[0] == TOK_LPAREN && type[1] == TOK_RPAREN)
		tokeniser_set_error(meta, str_vec_join((char *[5]){"ERROR : ", token[1]->raw, " cannot append ", token[0]->raw, 0}));
	else if (type[0] == TOK_WORD && type[1] == TOK_LPAREN)
		tokeniser_set_error(meta, str_vec_join((char *[5]){"ERROR : ", token[1]->raw, " cannot append ", token[0]->raw, 0}));
}
