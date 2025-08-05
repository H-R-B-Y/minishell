/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_condition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:46:17 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 17:27:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

static char *_continue_condition(const t_fsmdata *fsm,
	const t_tokretcode code
)
{
	(void)code;
	if (fsm->tok_int.curr_type == TOK_INCOMPLETE_STRING)
		return ("incomplete string");
	else if (fsm->state == ST_OPRA)
		return ("operation not finished");
	else if (fsm->paren_count > 0)
		return ("unclosed parenthesis");
	return ("continuing input");
}

static char	*_wrong_state_condition(const t_fsmdata *fsm,
	const t_tokretcode code
)
{
	(void)code;
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
		&& fsm->tok_int.curr_type == TOK_EOF)
		return ("expected deliminator");
	return ("unexpected token");
}

static char	*_error_condition(const t_fsmdata *fsm,
	const t_tokretcode code
)
{
	if (fsm->paren_count < 0)
		return ("mismatched parenthesis");
	else if (fsm->state == ST_WRNG)
		return (_wrong_state_condition(fsm, code));
	else if (fsm->tok_int.curr_type == TOK_ERR)
		return ("invalid token");
	return ("syntax error");
}

char	*get_condition_str(const t_fsmdata *fsm,
	const t_tokretcode code
)
{
	if (code == PARSE_CONT)
		return (_continue_condition(fsm, code));
	else if (code == PARSE_ERROR)
		return (_error_condition(fsm, code));
	else if (code == PARSE_FATAL)
		return ("unrecoverable error");
	return (0);
}
