/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:01:50 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 15:08:30 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;


int	better_add_history(t_minishell *shell, char *string)
{
	size_t		i;
	HIST_ENTRY	**the_history;
	size_t		h_len;
	// int			ret;
	char		*buff_str;

	if (!string || !*string)
		return (1);
	the_history = history_list();
	h_len = ft_arrlen((void **)the_history);
	i = 0;
	if (h_len)
		i= h_len - 1;
	buff_str = ft_strrtrim(string, "\n");
	if (!buff_str)
		perror_exit(shell, "add history");
	if (the_history && the_history[i])
	{
		if (!ft_strncmp(the_history[i]->line, buff_str,
			ft_strlen(the_history[i]->line) + 1))
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
		// printf("test: %s",shell->rldata.current_hist_item);
		better_add_history(shell, shell->rldata.current_hist_item);
		ft_dirtyswap((void *)&shell->rldata.current_hist_item, (void *)0, free);
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
