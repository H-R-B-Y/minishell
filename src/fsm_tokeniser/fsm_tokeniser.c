/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:19:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 17:22:24 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	destroy_token(t_token *token, void (*del_raw)(void *));
void	free_token_list(t_list *list, void (*del_raw)(void *));

t_fsmdata	*fsm(void)
{
	static t_fsmdata	fsm = {
		.state = ST_STRT,
		.last_state = ST_END,
		.retcode = PARSE_OK,
		.tokens = 0,
		.paren_count = 0,
		.tokeniser_internals = (t_tokint){0},
	};

	return (&fsm);
}

void	reset_tokeniser(void)
{
	if ((*fsm()).tokeniser_internals.current_token)
		destroy_token((*fsm()).tokeniser_internals.current_token, free);
	(*fsm()).tokeniser_internals = (t_tokint){
		.current_token = 0,
		.current_type = TOK_NONE,
		.index_end = 0,
		.index_start = 0,
		.quote_mode = QUOTE_NONE,
	};
}

void	reset_fsm(void)
{
	if ((*fsm()).tokens)
		free_token_list((*fsm()).tokens, free);
	reset_tokeniser();
	(*fsm()) = (t_fsmdata){
		.state = ST_STRT,
		.retcode = PARSE_OK,
		.tokens = 0,
		.tokeniser_internals = (*fsm()).tokeniser_internals,
		.paren_count = 0
	};
}

/*
	static const t_fsmtransition transitions[] = {
		{ST_STRT, "\10\13", ST_SUBSHELL}, // start can become a subshell
		{ST_STRT, "\3\4\5", ST_REDR}, // start can become a redirect
		{ST_STRT, "\6", ST_HDOC}, // start can become heredoc
		{ST_STRT, "\1", ST_WORD}, // word token to word state

		{ST_WORD, "\2\7\10\11\14", ST_OPRA}, // pipe, after, and, or, amp, to operator state
		{ST_WORD, "\3\4\5", ST_REDR}, // redirect in, redirect out, and redirect append
		{ST_WORD, "\10\13", ST_SUBSHELL},
		{ST_WORD, "\6", ST_HDOC},
		{ST_WORD, "\1", ST_WORD},

		{ST_REDR, "\1", ST_WORD},
		{ST_HDOC, "\1", ST_WORD},

		{ST_OPRA, "\3\4\5", ST_REDR},
		{ST_OPRA, "\10\13", ST_SUBSHELL}, // can transition into subshell
		{ST_OPRA, "\1", ST_WORD},

		{ST_SUBSHELL, "\2\7\10\11\14", ST_OPRA}, // Subshell MUST become an operator
		{ST_SUBSHELL, "\3\4\5", ST_REDR},
		{ST_SUBSHELL, "\6", ST_HDOC},
		{ST_SUBSHELL, "\10", ST_SUBSHELL}, // subshell can follow but not close right away

		{ST_WORD, "\15", ST_END},
		{ST_SUBSHELL, "\15", ST_END},
	};
*/

const t_fsmtransition	*_fsm_trns(void)
{
	static const t_fsmtransition transitions[] = {
		{ST_STRT, "\12\13", ST_LSSH}, {ST_STRT, "\3\4\5", ST_REDR},
		{ST_STRT, "\6", ST_HDOC}, {ST_STRT, "\1", ST_WORD},
		{ST_WORD, "\2\10\11", ST_OPRA}, {ST_WORD, "\7\14", ST_SEQ},
		{ST_WORD, "\15", ST_END}, {ST_WORD, "\3\4\5", ST_REDR},
		{ST_WORD, "\12", ST_LSSH}, {ST_WORD, "\13", ST_RSSH},
		{ST_WORD, "\6", ST_HDOC}, {ST_WORD, "\1", ST_WORD},
		{ST_REDR, "\1", ST_WORD}, {ST_HDOC, "\1", ST_WORD},
		{ST_OPRA, "\3\4\5", ST_REDR}, {ST_OPRA, "\12", ST_LSSH},
		{ST_OPRA, "\1", ST_WORD}, {ST_LSSH, "\1", ST_WORD},
		{ST_LSSH, "\3\4\5", ST_REDR}, {ST_LSSH, "\6", ST_HDOC},
		{ST_LSSH, "\12", ST_LSSH}, {ST_RSSH, "\15", ST_END},
		{ST_RSSH, "\13", ST_RSSH}, {ST_RSSH, "\2\10\11", ST_OPRA},
		{ST_RSSH, "\7\14", ST_SEQ}, {ST_RSSH, "\3\4\5", ST_REDR},
		{ST_RSSH, "\6", ST_HDOC}, {ST_SEQ, "\15", ST_END}
		
	};

	return (transitions);
}

t_fsmstate	fsm_check_transition(t_fsmstate current_state, t_tokentype next_token)
{
	size_t					i;
	const t_fsmtransition	*trns;

	i = 0;
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

t_token	*tokeniser_pop_token(void)
{
	t_token *p;

	p = TOKENISER.current_token;
	TOKENISER.current_token = 0;
	return (p);
}

