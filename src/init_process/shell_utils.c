/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:01:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/07 14:57:07 by hbreeze          ###   ########.fr       */
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

void	_destroy_token(void *t)
{
	destroy_token(t, free);
}

void	reset_for_command(t_minishell *shell)
{
	if (shell->rldata.current_hist_item)
	{
		if (!g_global_signal)
			better_add_history(shell->rldata.current_hist_item);
		ft_dirtyswap((void *)&shell->rldata.current_hist_item, (void *)0, free);
	}
	if (shell->rldata.last_line)
		ft_dirtyswap((void *)&shell->rldata.last_line, (void *)0, free);
	if (shell->rldata.extra_lines)
	{
		ft_arrclear((void *)shell->rldata.extra_lines, free);
		ft_dirtyswap((void *)&shell->rldata.extra_lines, (void *)0, free);
		shell->rldata.extra_line_count = 0;
	}
	ft_arrclear((void **)shell->tokenv, _destroy_token);
	destroy_ast(&shell->current_tree);
	reset_fsm(&shell->fsm_data);
	g_global_signal = 0;
}
