/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:19:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/17 14:58:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	reset_tokeniser(t_tokint *tokeniser)
{
	if (tokeniser->current_token)
		destroy_token(tokeniser->current_token, free);
	*tokeniser = (t_tokint){
		.current_token = 0,
		.current_type = TOK_NONE,
		.index_end = 0,
		.index_start = 0,
		.quote_mode = QUOTE_NONE,
	};
}

void	reset_fsm(t_fsmdata *fsm)
{
	if (fsm->tokens)
		free_token_list(fsm->tokens, free);
	if (fsm->str_condition)
		free(fsm->str_condition);
	reset_tokeniser(&fsm->tokeniser_internals);
	(*fsm) = (t_fsmdata){
		.state = ST_STRT, .retcode = PARSE_OK, .tokens = 0,
		.tokeniser_internals = fsm->tokeniser_internals,
		.paren_count = 0, .str_condition = 0,
	};
}

const t_fsmtransition	*_fsm_trns(void)
{
	static const t_fsmtransition transitions[TRNSCOUNT] = {
		{ST_STRT, "\12\13", ST_LSSH},
		{ST_STRT, "\3\4\5", ST_REDR},
		{ST_STRT, "\6", ST_HDOC},
		{ST_STRT, "\1", ST_WORD},
		{ST_WORD, "\2\10\11", ST_OPRA},
		{ST_WORD, "\7\14", ST_SEQ},
		{ST_WORD, "\15", ST_END},
		{ST_WORD, "\3\4\5", ST_REDR},
		{ST_WORD, "\12", ST_LSSH},
		{ST_WORD, "\13", ST_RSSH},
		{ST_WORD, "\6", ST_HDOC},
		{ST_WORD, "\1", ST_WORD},
		{ST_REDR, "\1", ST_WORD},
		{ST_HDOC, "\1", ST_WORD},
		{ST_OPRA, "\3\4\5", ST_REDR},
		{ST_OPRA, "\12", ST_LSSH},
		{ST_OPRA, "\1", ST_WORD},
		{ST_OPRA, "\15", ST_CONT},
		{ST_LSSH, "\1", ST_WORD},
		{ST_LSSH, "\3\4\5", ST_REDR},
		{ST_LSSH, "\6", ST_HDOC},
		{ST_LSSH, "\12", ST_LSSH},
		{ST_LSSH, "\15", ST_END},
		{ST_RSSH, "\15", ST_END},
		{ST_RSSH, "\13", ST_RSSH},
		{ST_RSSH, "\2\10\11", ST_OPRA},
		{ST_RSSH, "\7\14", ST_SEQ},
		{ST_RSSH, "\3\4\5", ST_REDR},
		{ST_RSSH, "\6", ST_HDOC},
		{ST_SEQ, "\15", ST_END},
		{ST_SEQ, "\1", ST_WORD},
		{ST_SEQ, "\3\4\5", ST_REDR},
		{ST_SEQ, "\6", ST_HDOC},
		{ST_SEQ, "\13", ST_RSSH},
		{ST_SEQ, "\12", ST_LSSH},
	};

	return (transitions);
}

t_fsmstate	fsm_check_transition(t_fsmstate current_state,
	t_tokentype next_token)
{
	size_t					i;
	const t_fsmtransition	*trns;

	i = 0;
	if (next_token == TOK_INCOMPLETE_STRING)
		return (ST_CONT);
	if (next_token == TOK_NONE)
		return (ST_WRNG);
	trns = _fsm_trns();
	while (i < TRNSCOUNT)
	{
		if (_fsm_trns()[i].from_state == current_state
			&& ft_strchr(_fsm_trns()[i].token_types, next_token))
			return (_fsm_trns()[i].too_state);
		i++;
	}
	return (ST_WRNG);
}

t_token	*tokeniser_pop_token(t_tokint *tokeniser)
{
	t_token *p;

	p = tokeniser->current_token;
	tokeniser->current_token = 0;
	return (p);
}
