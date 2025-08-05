/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:25:40 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 17:37:14 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fsm_tokeniser.h"

const char	*tokretcode_str(const t_tokretcode code)
{
	const char	*strs[TOKENISER_RETURNCODE_COUNT + 1] = {
		"Parse OK", "Parse Continue", "Parse Error",
		"Parse Fatal", "Parsed Nothing", "err"
	};

	if (code < 0 || code >= TOKENISER_RETURNCODE_COUNT)
		return (strs[TOKENISER_RETURNCODE_COUNT]);
	return (strs[code]);
}

const char	*fsmstate_str(const t_fsmstate state)
{
	const char	*strs[STATE_COUNT + 1] = {
		"Wrong state", "Start state", "Word", "Operator",
		"Sequence", "Subshell open", "Subshell close", "Heredoc",
		"Rediretion", "Continue State", "End State",
		"err"
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
