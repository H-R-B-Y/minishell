/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/22 14:21:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

// This to be renamed
// need to make sure this is the only place where the token type is
// determined, and that this doesn't just return something useless
t_tokentype	_parse_loop_internals(t_tokint *tokeniser, const char *str)
{
	char	c;

	while (str[tokeniser->index_end])
	{
		c = str[tokeniser->index_end];
		if (c == '\\' && tokeniser->quote_mode != QUOTE_SINGLE
			&& str[tokeniser->index_end + 1])
			tokeniser->index_end++;
		else if (tokeniser->quote_mode == QUOTE_DOUBLE && c == '"')
			tokeniser->quote_mode = QUOTE_NONE;
		else if (tokeniser->quote_mode == QUOTE_SINGLE && c == '\'')
			tokeniser->quote_mode = QUOTE_NONE;
		else if (tokeniser->quote_mode == QUOTE_NONE)
		{
			if (c == '\'')
				tokeniser->quote_mode = QUOTE_SINGLE;
			else if (c == '"')
				tokeniser->quote_mode = QUOTE_DOUBLE;
			else if (isoperator(c) || ft_iswhitespace(c) || c == '\0')
				return (tokenise_type(tokeniser, str));
		}
		tokeniser->index_end++;
	}
	return (tokenise_type(tokeniser, str));
}

t_tokentype	next_token_type(t_tokint *tokeniser, const char *str)
{
	tokeniser->index_start = tokeniser->index_end;
	if (tokeniser->quote_mode == QUOTE_NONE
		&& ft_iswhitespace(str[tokeniser->index_start]))
		tokeniser_skip_whitespace(tokeniser, str);
	if (tokeniser->quote_mode == QUOTE_NONE
		&& (isoperator(str[tokeniser->index_start])
			|| ft_isdigit(str[tokeniser->index_start])))
		return (handle_operator(tokeniser, str), tokenise_type(tokeniser, str));
	return (_parse_loop_internals(tokeniser, str));
}

t_tokretcode	set_retcode(t_fsmdata *fsm,
	const t_tokretcode code, char *str_condition)
{
	fsm->retcode = code;
	if (code == PARSE_CONT)
	{
		fsm->tokeniser_internals.index_end = 0;
		fsm->tokeniser_internals.index_start = 0;
	}
	if (fsm->str_condition)
		fsm->str_condition = 0;
	fsm->str_condition = str_condition;
	return (code);
}

void	state_change(t_fsmdata *fsm, t_fsmstate next_state)
{
	if (fsm->state == ST_HDOC && next_state == ST_WORD)
		fsm->tokeniser_internals.current_token->heredoc_delim = 1;
	else if (fsm->state == ST_REDR && next_state == ST_WORD)
		fsm->tokeniser_internals.current_token->redirect_file = 1;
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
		if (fsm->tokeniser_internals.current_type == TOK_INCOMPLETE_STRING)
			fsm->str_condition = "incomplete string";
		else if (fsm->state == ST_OPRA)
			fsm->str_condition = "operation not finished";
		else if (fsm->paren_count > 0)
		{
			fsm->str_condition = "unclosed parenthesis";
			handle_subshell_newline(fsm);
		}
		return (PARSE_CONT);
	}
	if (fsm->state == ST_END)
		return (state_change(fsm, ST_STRT), set_retcode(fsm, PARSE_OK, 0));
	return (set_retcode(fsm, PARSE_ERROR, "generic error"));
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
		fsm->tokeniser_internals.current_type
			= next_token_type(&fsm->tokeniser_internals, str);
		if (fsm->tokeniser_internals.current_type == TOK_ERR)
			return (set_retcode(fsm, PARSE_ERROR, "UNRECOVERABLE")); // maybe we should differenciate between errors and fatal errors
		next_state = fsm_check_transition(fsm->state,
				fsm->tokeniser_internals.current_type);
		if (!handle_token_type(fsm))
			next_state = ST_WRNG;
		state_change(fsm, next_state);
		if (next_state != ST_END && next_state != ST_WRNG
			&& next_state != ST_CONT)
			ft_lstadd_back(&(fsm->tokens),
				ft_lstnew(tokeniser_pop_token(&fsm->tokeniser_internals)));
	}
	return (correct_retcode(fsm));
}
