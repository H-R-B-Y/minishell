/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:24:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/26 17:56:52 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	read_with_temp_prompt(t_minishell *shell, char *temp)
{
	char	*temp_prmpt;
	int		code;

	temp_prmpt = ft_strjoin(temp, " > ");
	code = next_line(&shell->rldata, temp_prmpt);
	free(temp_prmpt);
	return (code);
}

int	read_until_complete_command(t_minishell *shell)
{
	t_readline_retcode	rl_code;
	t_tokretcode		fsm_code;

	if (shell->interactive_mode && !ft_dirtyswap((void *)&shell->prompt, (void *)create_prompt(shell), free))
		return (READ_FATAL);
	rl_code = next_line(&shell->rldata, shell->prompt);
	if (rl_code != READ_OK)
		return (rl_code);
	fsm_code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	while (fsm_code == PARSE_CONT)
	{
		rl_code = read_with_temp_prompt(shell, shell->fsm_data.str_condition);
		if (rl_code != READ_OK)
			return (rl_code);
		fsm_code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	}
	append_tokenv_to_history_item(shell, &shell->rldata, shell->fsm_data.tokens);
	if (fsm_code == PARSE_ERROR)
		return (READ_BADPARSE);
	else if (fsm_code == PARSE_FATAL)
		return (READ_FATAL);
	return (READ_OK);
}
