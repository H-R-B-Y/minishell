/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:01:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/04 14:18:25 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;


int	better_add_history(t_minishell *shell, char *string)
{
	char		*buff_str;

	if (!string || !*string || *string == ' ')
		return (1);
	buff_str = ft_strrtrim(string, "\n");
	if (!buff_str)
		perror_exit(shell, "add history");
	if (shell->last_hist_item)
	{
		if (!ft_strncmp(shell->last_hist_item, buff_str,
			ft_strlen(shell->last_hist_item) + 1))
			return (free(buff_str), 0);
	}
	add_history(buff_str);
	free(buff_str);
	return (1);
}

void	_destroy_token(void *t)
{
	destroy_token(t, free);
}

void	reset_for_command(t_minishell *shell, t_readline_retcode rl_code)
{
	if (shell->rldata.current_hist_item)
	{
		better_add_history(shell, shell->rldata.current_hist_item);
		ft_dirtyswap((void *)&shell->last_hist_item, ft_strdup(shell->rldata.current_hist_item), free);
		ft_dirtyswap((void *)&shell->rldata.current_hist_item, NULL, free);
	}
	if (shell->rldata.last_line)
		ft_dirtyswap((void *)&shell->rldata.last_line, (void *)0, free);
	if (shell->rldata.extra_lines
		&& (rl_code == READ_NOTHING
			|| rl_code == READ_EOF
			|| rl_code == READ_START))
	{
		ft_arrclear((void **)shell->rldata.extra_lines, free);
		shell->rldata.extra_line_count = 0;
	}
	ft_arrclear((void **)shell->tokenv, _destroy_token);
	shell->tokenv = 0;
	destroy_ast(&shell->current_tree);
	reset_fsm(&shell->fsm_data);
	g_global_signal = 0;
}
