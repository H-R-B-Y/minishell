/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 17:15:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

t_tokretcode	set_retcode(t_fsmdata *fsm,
	const t_tokretcode code, char *str_condition)
{
	fsm->retcode = code;
	if (code == PARSE_CONT)
	{
		fsm->tok_int.i_end = 0;
		fsm->tok_int.i_start = 0;
	}
	if (fsm->str_cond)
		fsm->str_cond = 0;
	fsm->str_cond = str_condition;
	return (code);
}

void	state_change(t_fsmdata *fsm, t_fsmstate next_state)
{
	if (fsm->state == ST_HDOC && next_state == ST_WORD)
		fsm->tok_int.curr_token->heredoc_delim = 1;
	else if (fsm->state == ST_REDR && next_state == ST_WORD)
		fsm->tok_int.curr_token->redirect_file = 1;
	if (next_state == ST_END && fsm->paren_count > 0)
		next_state = ST_CONT;
	fsm->last_state = fsm->state;
	fsm->state = next_state;
	dbg_add_state(fsm->debuginfo, fsm->state);
}

t_tokretcode	correct_retcode(t_fsmdata *fsm)
{
	if (fsm->paren_count < 0)
		return (set_retcode(fsm, PARSE_ERROR,
				"parenthesis dont make sense"));
	if (fsm->state == ST_CONT)
	{
		state_change(fsm, fsm->last_state);
		set_retcode(fsm, PARSE_CONT, 0);
		if (fsm->tok_int.curr_type == TOK_INCOMPLETE_STRING)
			fsm->str_cond = "incomplete string";
		else if (fsm->state == ST_OPRA)
			fsm->str_cond = "operation not finished";
		else if (fsm->paren_count > 0)
		{
			fsm->str_cond = "unclosed parenthesis";
			if (handle_subshell_newline(fsm) < 0)
				return (PARSE_FATAL);
		}
		return (PARSE_CONT);
	}
	if (fsm->state == ST_END)
		return (state_change(fsm, ST_STRT), set_retcode(fsm, PARSE_OK, 0));
	return (set_retcode(fsm, PARSE_ERROR, "generic error"));
}

static int	_accept_token(t_fsmdata *fsm, t_fsmstate *next_state)
{
	t_list	*token;

	if (!handle_token_type(fsm))
		*next_state = ST_WRNG;
	state_change(fsm, *next_state);
	if (*next_state != ST_END && *next_state != ST_WRNG
		&& *next_state != ST_CONT)
	{
		token = ft_lstnew(tokeniser_pop_token(&fsm->tok_int));
		if (!token)
			return (-1);
		ft_lstadd_back(&(fsm->tokens), token);
	}
	else
		destroy_token(tokeniser_pop_token(&fsm->tok_int), free);
	return (0);
}

t_tokretcode	tokenise(t_fsmdata *fsm, const char *str)
{
	t_fsmstate	next_state;

	if (fsm->retcode == PARSE_ERROR)
		reset_fsm(fsm);
	if (!str)
		return (set_retcode(fsm, PARSE_FATAL, "invalid string"));
	while (fsm->state != ST_END
		&& fsm->state != ST_CONT
		&& fsm->state != ST_WRNG)
	{
		fsm->tok_int.curr_type = next_token_type(&fsm->tok_int, str);
		if (fsm->tok_int.curr_type == TOK_EOF && fsm->state == ST_STRT)
			return (set_retcode(fsm, PARSE_NOTHING, 0));
		if (fsm->tok_int.curr_type == TOK_ERR)
			return (set_retcode(fsm, PARSE_FATAL, "UNRECOVERABLE"));
		next_state = fsm_check_transition(fsm->state, fsm->tok_int.curr_type);
		if (_accept_token(fsm, &next_state) < 0)
			return (set_retcode(fsm, PARSE_FATAL, "UNRECOVERABLE"));
	}
	return (correct_retcode(fsm));
}
