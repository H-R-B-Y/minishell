/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:24:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/29 17:28:48 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	read_with_temp_prompt(t_minishell *shell, char *temp)
{
	char	*temp_prmpt;
	int		code;

	temp_prmpt = ft_strjoin(temp, " > ");
	if (!temp_prmpt)
		perror_exit(shell, "minishell:readline_loop");
	code = next_line(&shell->rldata, temp_prmpt);
	free(temp_prmpt);
	return (code);
}

static int	_tokenise_loop(t_minishell *shell,
	t_tokretcode *code,
	t_readline_retcode *rl_code
)
{
	*code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	while (*code == PARSE_CONT)
	{
		*rl_code = read_with_temp_prompt(shell, shell->fsm_data.str_cond);
		if (*rl_code != READ_OK)
			return (-1);
		*code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	}
	return (0);
}

int	read_until_complete_command(t_minishell *shell)
{
	t_readline_retcode	rl_code;
	t_tokretcode		fsm_code;

	if (shell->interactive_mode && !ft_dirtyswap((void *)&shell->prompt,
			(void *)create_prompt(shell), free))
		perror_exit(shell, "minishell:readline_loop");
	rl_code = next_line(&shell->rldata, shell->prompt);
	if (rl_code != READ_OK)
		return (rl_code);
	if (_tokenise_loop(shell, &fsm_code, &rl_code) < 0)
		return (rl_code);
	if (fsm_code == PARSE_ERROR)
		return (READ_BADPARSE);
	else if (fsm_code == PARSE_FATAL)
		perror_exit(shell, "minishell:tokeniser");
	else if (fsm_code == PARSE_NOTHING)
		return (READ_NOTHING);
	return (READ_OK);
}
