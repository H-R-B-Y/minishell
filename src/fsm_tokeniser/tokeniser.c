/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 17:29:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

void	tokeniser_skip_whitespace(char *str);

t_token	*create_token(t_tokentype type, char *raw_token)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return ((void *)0);
	ft_bzero(tok, sizeof(t_token));
	tok->raw = raw_token;
	tok->type = type;
	return (tok);
}

void	destroy_token(t_token *token, void (*del_raw)(void *))
{
	if (!token)
		return ;
	if (token->raw && del_raw)
		del_raw(token->raw);
	free(token);
}

void	free_token_list(t_list *list, void (*del_raw)(void *))
{
	t_list	*start;
	t_list	*next;

	if (!list || !list->content)
		return ;
	start = list;
	while (start)
	{
		next = start->next;
		if (start->content)
			destroy_token(start->content, del_raw);
		free(start);
		start = next;
	}
}

void	free_token_vector(t_token **vec, void (*del_raw)(void *))
{
	size_t	i;

	if (!vec || !*vec)
		return ;
	i = 0;
	while (vec[i])
		destroy_token(vec[i++], del_raw);
}

t_tokentype	bin_token(const char *raw_token)
{
	if (!raw_token)
		return (TOK_NONE);
	if (!*raw_token)
		return (TOK_EOF);
	if (*raw_token == '\'' || *raw_token == '"')
		return (TOK_WORD);
	if (*raw_token == '|')
		return (TOK_PIPE + (7 * (raw_token[1]
			&& raw_token[1] == raw_token[0])));
	if (*raw_token == '>' || *raw_token == '<')
		return (TOK_REDIR_OUT + (2 * (raw_token[0] == '<'))
			+ (raw_token[1] && raw_token[0] == raw_token[1]));
	if (*raw_token == ';')
		return (TOK_AFTER);
	if (*raw_token == '&')
		return (TOK_AMP - (4 * (raw_token[1]
			&& raw_token[0] == raw_token[1])));
	if (*raw_token == '(' || *raw_token == ')')
		return (TOK_LPAREN + (*raw_token == ')'));
	return (TOK_WORD);
}

t_tokentype	tokenise_type(char *str)
{
	char *substring;

	substring = ft_substr(str, TOKENISER.index_start,
		TOKENISER.index_end - TOKENISER.index_start);
	TOKENISER.current_type = bin_token(substring);
	TOKENISER.current_token = ft_calloc(1, sizeof(t_token));
	(*TOKENISER.current_token) = (t_token){.heredoc_deliminator = 0,
		.raw = substring, .type = TOKENISER.current_type,};
	if (TOKENISER.current_type == TOK_WORD && TOKENISER.previous_line)
	{
		substring = ft_strjoin(TOKENISER.previous_line, substring);
		free(TOKENISER.current_token->raw);
		TOKENISER.current_token->raw = substring;
		free(TOKENISER.previous_line);
		TOKENISER.previous_line = 0;
	}
	return (TOKENISER.current_type);
}

t_tokentype		handle_operator(char *str)
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
	return (tokenise_type(str));
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
		return (handle_operator(str));
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
