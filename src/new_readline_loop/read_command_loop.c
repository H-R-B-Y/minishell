/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:24:13 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/12 17:35:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_with_temp_prompt(t_minishell *shell, char *temp)
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
	int	rl_code;
	int	fsm_code;

	ft_dirtyswap((void *)&shell->prompt, (void *)create_prompt(shell), free);
	rl_code = next_line(&shell->rldata, shell->prompt);
	if (rl_code != READ_OK)
		return (rl_code);
	fsm_code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	while (fsm_code == PARSE_CONT)
	{
		rl_code = read_with_temp_prompt(shell, shell->fsm_data.str_condition);
		// ft_dirtyswap((void *)&shell->fsm_data.str_condition, 0, free);
		if (rl_code != READ_OK)
			return (rl_code);
		fsm_code = tokenise(&shell->fsm_data, shell->rldata.last_line);
	}
	if (fsm_code == PARSE_ERROR)
		return (READ_BADPARSE);
	return (READ_OK);
}
