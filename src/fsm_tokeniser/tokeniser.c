/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 14:29:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

char	*get_condition_str(const t_fsmdata *fsm, const t_tokretcode code)
{
	if (code == PARSE_CONT)
	{
		if (fsm->tok_int.curr_type == TOK_INCOMPLETE_STRING)
			return ("incomplete string");
		else if (fsm->state == ST_OPRA)
			return ("operation not finished");
		else if (fsm->paren_count > 0)
			return ("unclosed parenthesis");
		return ("continuing input");
	}
	else if (code == PARSE_ERROR)
	{
		if (fsm->paren_count < 0)
			return ("mismatched parenthesis");
		else if (fsm->state == ST_WRNG)
		{
			if (fsm->tok_int.curr_type == TOK_PIPE)
				return ("unexpected pipe");
			else if (fsm->tok_int.curr_type >= TOK_REDIR_OUT
				&& fsm->tok_int.curr_type <= TOK_HEREDOC)
				return ("unexpected redirection");
			else if (fsm->tok_int.curr_type == TOK_AFTER)
				return ("unexpected semicolon");
			else if (fsm->last_state == ST_REDR
				&& fsm->tok_int.curr_type == TOK_EOF)
				return ("expected filename");
			else if (fsm->last_state == ST_HDOC
				&& fsm->tok_int.curr_type == TOK_EOF))
				return ("expected deliminator");
			return ("unexpected token");
		}
		else if (fsm->tok_int.curr_type == TOK_ERR)
			return ("invalid token");
		return ("syntax error");
	}
	else if (code == PARSE_FATAL)
		return ("unrecoverable error");
	return (0);
}

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
	if (str_condition)
		fsm->str_cond = str_condition;
	else
		fsm->str_cond = get_condition_str(fsm, code);
	if (fsm->tok_int.curr_token)
		destroy_token(tokeniser_pop_token(&fsm->tok_int), free);
	return (code);
}

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

t_tokretcode	parse_fatal(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_FATAL, 0));
}

t_tokretcode	parse_continue(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_CONT, 0));
}

t_tokretcode	parse_error(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_ERROR, 0));
}

t_tokretcode	parse_ok(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_OK, 0));
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
