/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/12 18:07:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokentype		_parse_loop_internals(t_tokint *tokeniser, char *str);

void	handle_potential_redirect(t_tokint *tokeniser, char *str)
{
	while (str[tokeniser->index_end] && isdigit(str[tokeniser->index_end]))
		tokeniser->index_end++;
	if (str[tokeniser->index_end] == '<')
	{
		tokeniser->index_end++;
		if (str[tokeniser->index_end] == '<')
			tokeniser->index_end++;
	}
	else if (str[tokeniser->index_end] == '>')
	{
		tokeniser->index_end++;
		if (str[tokeniser->index_end] == '>')
			tokeniser->index_end++;
		else if (str[tokeniser->index_end] == '&')
		{
			tokeniser->index_end++;
			if (ft_isdigit(str[tokeniser->index_end]))
				while (str[tokeniser->index_end]
					&& ft_isdigit(str[tokeniser->index_end]))
					tokeniser->index_end++;
			else if (str[tokeniser->index_end] == '-')
				tokeniser->index_end++;
		}
	}
	else
		_parse_loop_internals(tokeniser, str);
}

void	handle_operator(t_tokint *tokeniser, char *str)
{
	char	c;

	c = str[tokeniser->index_end];
	if (ft_isdigit(c) || c == '>')
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

void	handle_unclosed_quote(t_tokint *tokeniser, char *str)
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
