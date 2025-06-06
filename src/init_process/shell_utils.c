/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:01:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/06 15:45:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_global_signal;

int	better_add_history(char *string)
{
	size_t		i;
	HIST_ENTRY	**the_history;
	int			ret;

	the_history = history_list();
	i = 0;
	ret = 1;
	while (the_history && the_history[i])
	{
		if (!ft_strncmp(the_history[i]->line, string,
			ft_strlen(the_history[i]->line) + 1))
		{
			ret = 0;
			remove_history((int)i);
			break ;
		}
		i++;
	}
	add_history(string);
	return (ret);
}

void	reset_for_command(t_minishell *shell)
{
	if (shell->rldata.current_hist_item)
	{
		if (!g_global_signal)
			better_add_history(shell->rldata.current_hist_item);
		free(shell->rldata.current_hist_item);
		shell->rldata.current_hist_item = 0;
	}
	if (shell->rldata.extra_lines)
	{
		ft_arrclear((void *)shell->rldata.extra_lines, free);
		shell->rldata.extra_lines = 0;
		shell->rldata.extra_line_count = 0;
	}
	reset_fsm(&shell->fsm_data);
	g_global_signal = 0;
}
