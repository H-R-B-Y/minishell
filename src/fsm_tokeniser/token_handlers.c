/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:37:08 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 11:37:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_operator(t_tokint *tokeniser, char *str)
{
	char	c;

	c = str[tokeniser->index_start];
	if (c != ';' && c != '(' && c != ')'
		&& c == str[tokeniser->index_start + 1])
		tokeniser->index_end = tokeniser->index_start + 2;
	else
		tokeniser->index_end = tokeniser->index_start + 1;
}

void	handle_unclosed_quote(t_tokint *tokeniser, char *str)
{
	char	*temp;
	char	*temp2;

	if (tokeniser->previous_line)
	{
		temp = ft_substr(str, tokeniser->index_start,
			tokeniser->index_end - tokeniser->index_start);
		temp2 = str_vec_join((char *[4])
			{tokeniser->previous_line, temp, "\n", 0});
		free(tokeniser->previous_line);
		free(temp);
		tokeniser->previous_line = temp2;
		return ;
	}
	temp = ft_substr(str, tokeniser->index_start,
		tokeniser->index_end - tokeniser->index_start);
		tokeniser->previous_line = str_vec_join((char *[3]){
		temp, "\n", 0
	});
}

int	handle_token_type(t_fsmdata *fsm)
{
	if (fsm->tokeniser_internals.current_type == TOK_LPAREN)
		fsm->paren_count++;
	if (fsm->tokeniser_internals.current_type == TOK_RPAREN)
		fsm->paren_count--;
	if (fsm->paren_count < 0)
		return (0);
	if (fsm->tokeniser_internals.current_type == TOK_INCOMPLETE_STRING)
		return (0);
	return (1);
}

void	handle_subshell_newline(t_fsmdata *fsm)
{
	if (!(fsm->state != ST_OPRA && fsm->state != ST_SEQ))
		return ;
	append_anon_token(fsm, TOK_AFTER, ft_strdup(";"));
	state_change(fsm, ST_SEQ);
}
