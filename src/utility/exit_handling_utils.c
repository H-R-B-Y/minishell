/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:39:51 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/05 16:18:27 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_shell(t_minishell *shell)
{
	reset_for_command(shell, READ_NOTHING);
	fflush(stdout);
	free(shell->prompt);
	ft_arrclear((void *)shell->environment, free);
	restore_signals(shell);
	rl_clear_history();
	if (shell->last_hist_item)
		free(shell->last_hist_item);
}

void	clean_exit_status(t_minishell *shell, int status)
{
	clean_shell(shell);
	exit(status);
}

// TODO: test. ALso, maybe make a exit_message genral function to print and exit, success and failure
void	perror_exit(t_minishell *shell, char *message)
{
	ft_fprintf(2, "%s: ", shell->name);
	perror(message);
	if (errno == EISDIR)
		clean_exit_status(shell, 126);
	else
		clean_exit_status(shell, EXIT_FAILURE);
}

void _free_arr_perror_exit(t_minishell *shell, void **arr, char *message)
{
	ft_arrclear((void **)arr, free);
	perror_exit(shell, message);
}

void	_set_returncode(int *to_set, int code)
{
	if (WIFEXITED(code))
		*to_set = WEXITSTATUS(code);
	else if (WIFSIGNALED(code))
		*to_set = 128 + WTERMSIG(code);
	else
		*to_set = 1;
}
