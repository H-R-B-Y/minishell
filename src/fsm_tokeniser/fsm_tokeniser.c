/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_tokeniser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:19:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 14:23:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	destroy_token(t_token *token, void (*del_raw)(void *));
void	free_token_list(t_list *list, void (*del_raw)(void *));

t_fsmdata	*fsm(void)
{
	static t_fsmdata	fsm = {
		.state = ST_START,
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
		.state = ST_START,
		.retcode = PARSE_OK,
		.tokens = 0,
		.tokeniser_internals = (*fsm()).tokeniser_internals,
		.paren_count = 0
	};
}

/*
	static const t_fsmtransition transitions[] = {
		{ST_START, "\10\13", ST_SUBSHELL}, // start can become a subshell
		{ST_START, "\3\4\5", ST_REDIRECT}, // start can become a redirect
		{ST_START, "\6", ST_HEREDOC}, // start can become heredoc
		{ST_START, "\1", ST_WORD}, // word token to word state

		{ST_WORD, "\2\7\10\11\14", ST_OPERATOR}, // pipe, after, and, or, amp, to operator state
		{ST_WORD, "\3\4\5", ST_REDIRECT}, // redirect in, redirect out, and redirect append
		{ST_WORD, "\10\13", ST_SUBSHELL},
		{ST_WORD, "\6", ST_HEREDOC},
		{ST_WORD, "\1", ST_WORD},

		{ST_REDIRECT, "\1", ST_WORD},
		{ST_HEREDOC, "\1", ST_WORD},

		{ST_OPERATOR, "\3\4\5", ST_REDIRECT},
		{ST_OPERATOR, "\10\13", ST_SUBSHELL}, // can transition into subshell
		{ST_OPERATOR, "\1", ST_WORD},

		{ST_SUBSHELL, "\2\7\10\11\14", ST_OPERATOR}, // Subshell MUST become an operator
		{ST_SUBSHELL, "\3\4\5", ST_REDIRECT},
		{ST_SUBSHELL, "\6", ST_HEREDOC},
		{ST_SUBSHELL, "\10", ST_SUBSHELL}, // subshell can follow but not close right away

		{ST_WORD, "\15", ST_END},
		{ST_SUBSHELL, "\15", ST_END},
	};
*/

const t_fsmtransition	*_fsm_trns(void)
{
	static const t_fsmtransition transitions[TRNSCOUNT] = {
		{ST_START, "\10\13", ST_SUBSHELL}, {ST_START, "\3\4\5", ST_REDIRECT},
		{ST_START, "\6", ST_HEREDOC}, {ST_START, "\1", ST_WORD},
		{ST_WORD, "\2\7\10\11\14", ST_OPERATOR},
		{ST_WORD, "\3\4\5", ST_REDIRECT}, {ST_WORD, "\10\13", ST_SUBSHELL},
		{ST_WORD, "\6", ST_HEREDOC}, {ST_WORD, "\1", ST_WORD},
		{ST_REDIRECT, "\1", ST_WORD}, {ST_HEREDOC, "\1", ST_WORD},
		{ST_OPERATOR, "\3\4\5", ST_REDIRECT},
		{ST_OPERATOR, "\10\13", ST_SUBSHELL}, {ST_OPERATOR, "\1", ST_WORD},
		{ST_SUBSHELL, "\2\7\10\11\14", ST_OPERATOR},
		{ST_SUBSHELL, "\3\4\5", ST_REDIRECT}, {ST_SUBSHELL, "\6", ST_HEREDOC},
		{ST_SUBSHELL, "\10", ST_SUBSHELL}, {ST_WORD, "\15", ST_END},
		{ST_SUBSHELL, "\15", ST_END},
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
	return (ST_WRONG);
}
