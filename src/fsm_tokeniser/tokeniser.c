/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 17:36:58 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void		handle_operator(char *str)
{
	char	c;

	if (!isoperator(str[TOKENISER.index_start]))
		return (TOK_NONE);
	c = str[TOKENISER.index_start];
	if (c != ';' && c != '(' && c != ')'
		&& c == str[TOKENISER.index_start + 1])
		TOKENISER.index_end = TOKENISER.index_start + 2;
	else
		TOKENISER.index_end = TOKENISER.index_start + 1;
}

void	handle_unclosed_quote(char *str)
{
	char	temp;

	if (!TOKENISER.previous_line)
		TOKENISER.previous_line = ft_substr(str, TOKENISER.index_start,
			TOKENISER.index_end - TOKENISER.index_start);
	else
	{
		temp = ft_strjoin(TOKENISER.previous_line, ft_substr(str,
			TOKENISER.index_start, TOKENISER.index_end - TOKENISER.index_start));
		free(TOKENISER.previous_line);
		TOKENISER.previous_line = temp;
	}
}

t_tokentype		next_token_type(char *str)
{
	TOKENISER.index_start = TOKENISER.index_end;
	if (!str[TOKENISER.index_start])
		return (TOK_EOF);
	if (ft_iswhitespace(str[TOKENISER.index_start]))
		tokeniser_skip_whitespace(str);
	if (isoperator(str[TOKENISER.index_start]))
		return (handle_operator(str), tokenise_type(str));
	while (str[TOKENISER.index_end])
	{
		if (CUR_QUOTEMODE == QUOTE_NONE)
		{
			if (str[TOKENISER.index_end] == '\'')
				CUR_QUOTEMODE = QUOTE_SINGLE;
			else if (str[TOKENISER.index_end] == '"')
				CUR_QUOTEMODE = QUOTE_DOUBLE;
			else if (isoperator(str[TOKENISER.index_end]))
				return (tokenise_type(str));
			else if (ft_iswhitespace(str[TOKENISER.index_end])
				|| str[TOKENISER.index_end] == '\0')
				return (tokenise_type(str));
		}
		else if (CUR_QUOTEMODE == QUOTE_DOUBLE
			&& str[TOKENISER.index_end] == '"')
			CUR_QUOTEMODE = QUOTE_NONE;
		else if (CUR_QUOTEMODE == QUOTE_SINGLE
			&& str[TOKENISER.index_end] == '\'')
			CUR_QUOTEMODE = QUOTE_NONE;
		TOKENISER.index_end++;
	}
	if (CUR_QUOTEMODE != QUOTE_NONE)
		return (handle_unclosed_quote(str), TOK_INCOMPLETE_STRING);
	else if (TOKENISER.index_start < TOKENISER.index_end)
		return (tokenise_type(str));
	return (TOK_EOF);
}

t_tokretcode	set_retcode(t_tokretcode code)
{
	FSM.retcode = code;
	if (code == PARSE_CONT)
	{
		TOKENISER.index_end = 0;
		TOKENISER.index_start = 0;
	}
	return (code);
}

void	state_change(t_fsmstate next_state)
{
	printf("handle transition: %s to %s\n", fsmstate_str(FSM.state),
		fsmstate_str(next_state));
	if (next_state != ST_END && next_state != ST_WRNG)
		ft_lstadd_back(&(FSM.tokens), ft_lstnew(tokeniser_pop_token()));
	FSM.last_state = FSM.state;
	FSM.state = next_state;
}

t_tokretcode	correct_retcode(char *str)
{
	if (FSM.paren_count < 0)
		return (set_retcode(PARSE_ERROR));
	else if (FSM.state == ST_WRNG && FSM.last_state == ST_OPRA)
		return (state_change(FSM.last_state), set_retcode(PARSE_CONT));
	else if (TOKENISER.current_type == TOK_INCOMPLETE_STRING)
		return (set_retcode(PARSE_CONT));
	else if (FSM.state == ST_END && FSM.paren_count > 0)
		return (state_change(FSM.last_state), set_retcode(PARSE_CONT));
	else if (FSM.state == ST_END)
		return (state_change(ST_STRT), set_retcode(PARSE_OK));
	return (set_retcode(PARSE_ERROR));
}

int	handle_token_type(char *str)
{
	if (TOKENISER.current_type == TOK_LPAREN)
		FSM.paren_count++;
	if (TOKENISER.current_type == TOK_RPAREN)
		FSM.paren_count--;
	if (FSM.paren_count < 0)
		return (0);
	if (TOKENISER.current_type == TOK_INCOMPLETE_STRING)
		return (0);
	return (1);
}


t_tokretcode	tokenise(char *str)
{
	t_fsmstate	next_state;

	if (!str || FSM.retcode == PARSE_ERROR)
		return (reset_fsm(), PARSE_ERROR);
	while (FSM.state != ST_END)
	{
		TOKENISER.current_type = next_token_type(str);
		if (!handle_token_type(str))
			return (correct_retcode(str));
		next_state = fsm_check_transition(FSM.state, TOKENISER.current_type);
		state_change(next_state);
		if (next_state == ST_WRNG)
			return (correct_retcode(str));
	}
	return (correct_retcode(str));
}
