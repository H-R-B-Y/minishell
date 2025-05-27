/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:25:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/23 20:39:16 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

const char	*tokretcode_str(t_tokretcode code)
{
	const char	*strs[TOKENISER_RETURNCODE_COUNT + 1] = {
		"PARSE_OK", "PARSE_CONT", "PARSE_ERROR",
		"to string error"
	};

	if (code < 0 || code >= TOKENISER_RETURNCODE_COUNT)
		return (strs[TOKENISER_RETURNCODE_COUNT]);
	return (strs[code]);
}

const char	*fsmstate_str(t_fsmstate state)
{
	const char	*strs[STATE_COUNT + 1] = {
		"Wrong state", "starting state", "word", "operator",
		"sequence", "subshell open", "subshell close", "heredoc",
		"redirection", "continue state", "end state",
		"to string error"
	};

	if (state < 0 || state >= STATE_COUNT)
		return (strs[STATE_COUNT]);
	return (strs[state]);
}

t_list	*fsm_pop_list(t_fsmdata *fsm)
{
	t_list	*temp;

	temp = fsm->tokens;
	fsm->tokens = 0;
	return (temp);
}
