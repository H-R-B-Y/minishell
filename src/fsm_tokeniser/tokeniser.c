/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 11:38:00 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

t_tokentype		next_token_type(t_tokint *tokeniser, char *str)
{
	tokeniser->index_start = tokeniser->index_end;
	if (!str[tokeniser->index_start])
		return (TOK_EOF);
	if (ft_iswhitespace(str[tokeniser->index_start]))
		tokeniser_skip_whitespace(tokeniser, str);
	if (tokeniser->quote_mode == QUOTE_NONE
		&& isoperator(str[tokeniser->index_start]))
		return (handle_operator(tokeniser, str), tokenise_type(tokeniser, str));
	while (str[tokeniser->index_end])
	{
		if (tokeniser->quote_mode == QUOTE_NONE)
		{
			if (str[tokeniser->index_end] == '\'')
				tokeniser->quote_mode = QUOTE_SINGLE;
			else if (str[tokeniser->index_end] == '"')
				tokeniser->quote_mode = QUOTE_DOUBLE;
			else if (isoperator(str[tokeniser->index_end]))
				return (tokenise_type(tokeniser, str));
			else if (ft_iswhitespace(str[tokeniser->index_end])
				|| str[tokeniser->index_end] == '\0')
				return (tokenise_type(tokeniser, str));
		}
		else if (tokeniser->quote_mode == QUOTE_DOUBLE
			&& str[tokeniser->index_end] == '"')
			tokeniser->quote_mode = QUOTE_NONE;
		else if (tokeniser->quote_mode == QUOTE_SINGLE
			&& str[tokeniser->index_end] == '\'')
			tokeniser->quote_mode = QUOTE_NONE;
		tokeniser->index_end++;
	}
	if (tokeniser->quote_mode != QUOTE_NONE)
		return (handle_unclosed_quote(tokeniser, str), TOK_INCOMPLETE_STRING);
	else if (tokeniser->index_start < tokeniser->index_end)
		return (tokenise_type(tokeniser, str));
	return (TOK_EOF);
}

t_tokretcode	set_retcode(t_fsmdata *fsm, t_tokretcode code, char *str_condition)
{
	fsm->retcode = code;
	if (code == PARSE_CONT)
	{
		fsm->tokeniser_internals.index_end = 0;
		fsm->tokeniser_internals.index_start = 0;

	}
	if (str_condition)
	{
		if (fsm->str_condition)
			free(fsm->str_condition);
		fsm->str_condition = str_condition;
	}
	return (code);
}

void	state_change(t_fsmdata *fsm, t_fsmstate next_state)
{
	printf("handle transition: %s to %s\n", fsmstate_str(fsm->state),
		fsmstate_str(next_state));
	// I kind of want to add some function lookup here,
	// it would be good to have some kind of function map that 
	// could be indexed by the states, then on certain transitions
	
	// what kind of state transitions do we need to do?
	// HEREDOC to WORD = word token should be marked
	// REDIRECT to WORD = word token should be marked
	
	// if that is it then we dont need to create a function matrix
	// we can just handle these cases
	if (fsm->state == ST_HDOC && next_state == ST_WORD)
		fsm->tokeniser_internals.current_token->heredoc_delim = 1;
	else if (fsm->state == ST_REDR && next_state == ST_WORD)
		fsm->tokeniser_internals.current_token->redirect_file = 1;
	fsm->last_state = fsm->state;
	fsm->state = next_state;
}

t_tokretcode	correct_retcode(t_fsmdata *fsm)
{
	if (fsm->paren_count < 0)
		return (set_retcode(fsm, PARSE_ERROR,
			ft_strdup("parenthesis dont make sense")));
	else if (fsm->state == ST_WRNG && fsm->last_state == ST_OPRA)
		return (state_change(fsm, fsm->last_state), set_retcode(fsm, PARSE_CONT,
			ft_strdup("operation not finished")));
	else if (fsm->tokeniser_internals.current_type == TOK_INCOMPLETE_STRING)
		return (set_retcode(fsm, PARSE_CONT, ft_strdup("incomplete string")));
	else if (fsm->state == ST_END && fsm->paren_count > 0)
	{
		state_change(fsm, fsm->last_state);
		handle_subshell_newline(fsm);
		return (set_retcode(fsm, PARSE_CONT,
			ft_strdup("incomplete parenthesis")));
	}
	else if (fsm->state == ST_END)
		return (state_change(fsm, ST_STRT), set_retcode(fsm, PARSE_OK, 0));
	return (set_retcode(fsm, PARSE_ERROR, ft_strdup("generic error")));
}



t_tokretcode	tokenise(t_fsmdata *fsm, char *str)
{
	t_fsmstate	next_state;

	if (!str || fsm->retcode == PARSE_ERROR)
		return (reset_fsm(fsm), PARSE_ERROR);
	while (fsm->state != ST_END)
	{
		fsm->tokeniser_internals.current_type = next_token_type(&fsm->tokeniser_internals, str);
		if (!handle_token_type(fsm))
			return (correct_retcode(fsm));
		next_state = fsm_check_transition(fsm->state,
			fsm->tokeniser_internals.current_type);
		state_change(fsm, next_state);
		if (next_state != ST_END && next_state != ST_WRNG)
			ft_lstadd_back(&(fsm->tokens), ft_lstnew(tokeniser_pop_token(&fsm->tokeniser_internals)));
		if (next_state == ST_WRNG)
			return (correct_retcode(fsm));
	}
	return (correct_retcode(fsm));
}
