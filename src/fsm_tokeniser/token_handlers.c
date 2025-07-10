/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/10 13:42:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokentype		parse_word_token(t_tokint *tokeniser, const char *str);

void	handle_potential_redirect(t_tokint *tokeniser, const char *str)
{
	char	t;

	while (str[tokeniser->index_end] && isdigit(str[tokeniser->index_end]))
		tokeniser->index_end++;
	t = str[tokeniser->index_end];
	if ((!(t == '<' || t == '>'))
		&& (parse_word_token(tokeniser, str) || 1))
		return ;
	tokeniser->index_end++;
	if (str[tokeniser->index_end] == t)
		tokeniser->index_end++;
	else if (str[tokeniser->index_end] == '&')
	{
		tokeniser->index_end++;
		while (ft_iswhitespace(str[tokeniser->index_end]))
			tokeniser->index_end++;
		if (ft_isdigit(str[tokeniser->index_end]))
			while (str[tokeniser->index_end] 
				&& (ft_isdigit(str[tokeniser->index_end])))
				tokeniser->index_end++;
		else if (str[tokeniser->index_end] == '-')
			tokeniser->index_end++;
	}
}

void	handle_operator(t_tokint *tokeniser, const char *str)
{
	char	c;

	c = str[tokeniser->index_end];
	if (ft_isdigit(c) || c == '>' || c == '<')
		handle_potential_redirect(tokeniser, str);
	else if (c == '&' && str[tokeniser->index_end + 1] == '>')
		tokeniser->index_end += 2 + (1 * (str[tokeniser->index_end + 1]
					== str[tokeniser->index_end + 2]));
	else if (!ft_strchr(";()", c)
		&& c == str[tokeniser->index_end + 1])
		tokeniser->index_end = tokeniser->index_end + 2;
	else
		tokeniser->index_end = tokeniser->index_end + 1;
}

void	handle_unclosed_quote(t_tokint *tokeniser, const char *str)
{
	char	*temp;

	temp = ft_substr(str, tokeniser->index_start,
			tokeniser->index_end - tokeniser->index_start);
	if (tokeniser->previous_line)
		ft_dirtyswap((void *)&tokeniser->previous_line,
			str_vec_join((char *[4]){tokeniser->previous_line, temp, "\n", 0}),
			free);
	else
		ft_dirtyswap((void *)&tokeniser->previous_line,
			str_vec_join((char *[3]){temp, "\n", 0}),
			free);
	free(temp);
}

int	handle_token_type(t_fsmdata *fsm)
{
	if (fsm->tokeniser_internals.previous_line
		&& fsm->tokeniser_internals.current_type != TOK_WORD
		&& fsm->tokeniser_internals.current_type != TOK_INCOMPLETE_STRING)
	{
		append_anon_token(fsm, TOK_WORD,
			fsm->tokeniser_internals.previous_line);
		fsm->tokeniser_internals.previous_line = 0;
	}
	if (fsm->tokeniser_internals.current_type == TOK_LPAREN)
		fsm->paren_count++;
	if (fsm->tokeniser_internals.current_type == TOK_RPAREN)
		fsm->paren_count--;
	if (fsm->paren_count < 0)
		return (0);
	return (1);
}

void	handle_subshell_newline(t_fsmdata *fsm)
{
	if (!(fsm->state != ST_OPRA && fsm->state != ST_SEQ
			&& fsm->state != ST_LSSH))
		return ;
	append_anon_token(fsm, TOK_AFTER, ft_strdup(";"));
	state_change(fsm, ST_SEQ);
}
