/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:22:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 14:34:00 by hbreeze          ###   ########.fr       */
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

	substring = ft_substr(str, TOKENISER.index_start, TOKENISER.index_end);
	TOKENISER.current_type = bin_token(substring);
	TOKENISER.current_token = ft_calloc(1, sizeof(t_token));
	(*TOKENISER.current_token) = (t_token){
		.heredoc_deliminator = 0,
		.raw = substring,
		.type = TOKENISER.current_type,
	};
	return (TOKENISER.current_type);
}

t_tokentype		handle_operator(char *str)
{
	
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
			else if (ft_iswhitespace(str[TOKENISER.index_end]))
				return (tokenise_type(str));
		}
		else if (CUR_QUOTEMODE == QUOTE_DOUBLE && str[TOKENISER.index_end] == '"')
			CUR_QUOTEMODE = QUOTE_NONE;
		else if (CUR_QUOTEMODE == QUOTE_SINGLE && str[TOKENISER.index_end] == '\'')
			CUR_QUOTEMODE = QUOTE_NONE;
		TOKENISER.index_end++;
	}
	if (CUR_QUOTEMODE != QUOTE_NONE)
		return (TOK_INCOMPLETE_STRING);
	return (TOK_EOF);
}



t_tokretcode	set_retcode(t_tokretcode code)
{
	FSM.retcode = code;
	return (code);
}

t_tokretcode	correct_retcode(char *str)
{
	(void)str;
	if (FSM.state == ST_WRONG || FSM.paren_count < 0)
		return (set_retcode(PARSE_ERROR));
	else if (FSM.state == ST_END)
	{
		if (FSM.paren_count > 0)
			return (set_retcode(PARSE_CONTINUE));
		else if (TOKENISER.quote_mode != QUOTE_NONE)
			return (set_retcode(PARSE_CONTINUE));
		return (set_retcode(PARSE_OK));
	}
	return (set_retcode(PARSE_ERROR));
}

void	handle_token_type(void)
{
	if (TOKENISER.current_type == TOK_LPAREN)
		FSM.paren_count++;
	if (TOKENISER.current_type == TOK_RPAREN)
		FSM.paren_count--;
}

void	handle_state_change(t_fsmstate next_state)
{
	(void)next_state;
	printf("handle state transition here\n");
	ft_lstadd_back(&(FSM.tokens), ft_lstnew(TOKENISER.current_token));
}

t_tokretcode	tokenise(char *str)
{
	t_fsmstate	next_state;

	if (!str || FSM.retcode == PARSE_ERROR)
		return (reset_fsm(), PARSE_ERROR);
	while (TOKENISER.current_type != TOK_EOF)
	{
		TOKENISER.current_type = next_token_type(str);
		handle_token_type();
		if (TOKENISER.current_type == TOK_INCOMPLETE_STRING
			|| FSM.paren_count < 0)
			return (correct_retcode(str));
		next_state = fsm_check_transition(FSM.state, TOKENISER.current_type);
		if (next_state == ST_WRONG)
			return (set_retcode(PARSE_ERROR));
		else
			handle_state_change(next_state);
		FSM.state = next_state;
	}
	return (correct_retcode(str));
}
