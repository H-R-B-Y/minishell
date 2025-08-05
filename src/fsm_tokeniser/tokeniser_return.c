/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:50:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 16:51:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"
#include "../../include/v_dbg.h"

char	*get_condition_str(const t_fsmdata *fsm, const t_tokretcode code);

t_tokretcode	set_retcode(t_fsmdata *fsm,
	const t_tokretcode code,
	char *str_condition
)
{
	fsm->retcode = code;
	if (code == PARSE_CONT)
	{
		fsm->tok_int.i_end = 0;
		fsm->tok_int.i_start = 0;
	}
	if (fsm->str_cond)
		fsm->str_cond = 0;
	if (str_condition)
		fsm->str_cond = str_condition;
	else
		fsm->str_cond = get_condition_str(fsm, code);
	if (fsm->tok_int.curr_token)
		destroy_token(tokeniser_pop_token(&fsm->tok_int), free);
	return (code);
}


t_tokretcode	parse_fatal(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_FATAL, 0));
}

t_tokretcode	parse_continue(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_CONT, 0));
}

t_tokretcode	parse_error(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_ERROR, 0));
}

t_tokretcode	parse_ok(t_fsmdata *fsm)
{
	return (set_retcode(fsm, PARSE_OK, 0));
}