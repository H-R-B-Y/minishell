/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 18:33:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

t_tokentype		next_token_type(char *str)
{
	(*tokeniser()).index_start = (*tokeniser()).index_end;
	if (!str[(*tokeniser()).index_start])
		return (TOK_EOF);
	if (ft_iswhitespace(str[(*tokeniser()).index_start]))
		tokeniser_skip_whitespace(str);
	if (tokeniser()->quote_mode == QUOTE_NONE && isoperator(str[(*tokeniser()).index_start]))
		return (handle_operator(str), tokenise_type(str));
	while (str[(*tokeniser()).index_end])
	{
		if (tokeniser()->quote_mode == QUOTE_NONE)
		{
			if (str[(*tokeniser()).index_end] == '\'')
				tokeniser()->quote_mode = QUOTE_SINGLE;
			else if (str[(*tokeniser()).index_end] == '"')
				tokeniser()->quote_mode = QUOTE_DOUBLE;
			else if (isoperator(str[(*tokeniser()).index_end]))
				return (tokenise_type(str));
			else if (ft_iswhitespace(str[(*tokeniser()).index_end])
				|| str[(*tokeniser()).index_end] == '\0')
				return (tokenise_type(str));
		}
		else if (tokeniser()->quote_mode == QUOTE_DOUBLE
			&& str[(*tokeniser()).index_end] == '"')
			tokeniser()->quote_mode = QUOTE_NONE;
		else if (tokeniser()->quote_mode == QUOTE_SINGLE
			&& str[(*tokeniser()).index_end] == '\'')
			tokeniser()->quote_mode = QUOTE_NONE;
		(*tokeniser()).index_end++;
	}
	if (tokeniser()->quote_mode != QUOTE_NONE)
		return (handle_unclosed_quote(str), TOK_INCOMPLETE_STRING);
	else if ((*tokeniser()).index_start < (*tokeniser()).index_end)
		return (tokenise_type(str));
	return (TOK_EOF);
}

t_tokretcode	set_retcode(t_tokretcode code)
{
	(*fsm()).retcode = code;
	if (code == PARSE_CONT)
	{
		(*tokeniser()).index_end = 0;
		(*tokeniser()).index_start = 0;
	}
	return (code);
}

void	state_change(t_fsmstate next_state)
{
	printf("handle transition: %s to %s\n", fsmstate_str((*fsm()).state),
		fsmstate_str(next_state));
	(*fsm()).last_state = (*fsm()).state;
	(*fsm()).state = next_state;
}

t_tokretcode	correct_retcode()
{
	if ((*fsm()).paren_count < 0)
		return (set_retcode(PARSE_ERROR));
	else if ((*fsm()).state == ST_WRNG && (*fsm()).last_state == ST_OPRA)
		return (state_change((*fsm()).last_state), set_retcode(PARSE_CONT));
	else if ((*tokeniser()).current_type == TOK_INCOMPLETE_STRING)
		return (set_retcode(PARSE_CONT));
	else if ((*fsm()).state == ST_END && (*fsm()).paren_count > 0)
	{
		state_change((*fsm()).last_state);
		handle_subshell_newline();
		return ( set_retcode(PARSE_CONT));
	}
	else if ((*fsm()).state == ST_END)
		return (state_change(ST_STRT), set_retcode(PARSE_OK));
	return (set_retcode(PARSE_ERROR));
}



t_tokretcode	tokenise(char *str)
{
	t_fsmstate	next_state;

	if (!str || (*fsm()).retcode == PARSE_ERROR)
		return (reset_fsm(), PARSE_ERROR);
	while ((*fsm()).state != ST_END)
	{
		(*tokeniser()).current_type = next_token_type(str);
		if (!handle_token_type())
			return (correct_retcode());
		next_state = fsm_check_transition((*fsm()).state,
			(*tokeniser()).current_type);
		state_change(next_state);
		if (next_state != ST_END && next_state != ST_WRNG)
			ft_lstadd_back(&((*fsm()).tokens), ft_lstnew(tokeniser_pop_token()));
		if (next_state == ST_WRNG)
			return (correct_retcode());
	}
	return (correct_retcode());
}
