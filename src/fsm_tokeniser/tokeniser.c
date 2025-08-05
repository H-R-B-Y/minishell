/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 17:37:24 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

t_tokretcode	set_retcode(t_fsmdata *fsm,
	const t_tokretcode code, char *str_condition);
t_tokretcode	parse_fatal(t_fsmdata *fsm);
t_tokretcode	parse_continue(t_fsmdata *fsm);
t_tokretcode	parse_error(t_fsmdata *fsm);
t_tokretcode	parse_ok(t_fsmdata *fsm);


static int	_accept_token(t_fsmdata *fsm)
{
	t_list	*token;

	if (fsm->state != ST_END && fsm->state != ST_WRNG
		&& fsm->state != ST_CONT)
	{
		token = ft_lstnew(tokeniser_pop_token(&fsm->tok_int));
		if (!token)
			return (-1);
		ft_lstadd_back(&(fsm->tokens), token);
	}
	return (0);
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
		return (parse_error(fsm));
	if (fsm->state == ST_CONT)
	{
		state_change(fsm, fsm->last_state);
		if (fsm->paren_count > 0 && handle_subshell_newline(fsm) < 0)
			return (parse_fatal(fsm));
		return (parse_continue(fsm));
	}
	if (fsm->state == ST_END)
		return (state_change(fsm, ST_STRT), parse_ok(fsm));
	return (parse_error(fsm));
}

t_fsmstate	get_next_state(t_fsmdata *fsm)
{
	t_fsmstate	next_state;

	next_state = fsm_check_transition(fsm->state, fsm->tok_int.curr_type);
	if (fsm->tok_int.curr_type == TOK_LPAREN)
		fsm->paren_count++;
	if (fsm->tok_int.curr_type == TOK_RPAREN)
		fsm->paren_count--;
	if (fsm->paren_count < 0)
		next_state = ST_WRNG;
	state_change(fsm, next_state);
	return (next_state);
}

t_tokretcode	tokenise(t_fsmdata *fsm, const char *str)
{
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
			return (parse_fatal(fsm));
		get_next_state(fsm);
		if (_accept_token(fsm) < 0)
			return (parse_fatal(fsm));
	}
	return (correct_retcode(fsm));
}
