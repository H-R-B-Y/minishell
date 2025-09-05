/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:48:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/19 15:42:38 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_int_handle_interactive(int sig, siginfo_t *info, void *context);
ssize_t	get_ulimitn(void);
int		check_stdfds(void);
void	init_xvars(t_minishell *shell, char ***envp);

static int	event(void)
{
	return (0);
}

int	signals_interactive(t_minishell *shell, struct sigaction *act)
{
	(void)shell;
	act->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, act, 0);
	sigaction(SIGTSTP, act, 0);
	act->sa_flags |= SA_SIGINFO;
	act->sa_flags |= SA_RESTART;
	act->sa_handler = 0;
	act->sa_sigaction = sig_int_handle_interactive;
	sigaction(SIGINT, act, 0);
	rl_event_hook = event;
	return (0);
}

int	signals_non_interactive(t_minishell *shell, struct sigaction *act)
{
	(void)shell;
	(void)act;
	return (0);
}

//       SA_SIGINFO (since Linux 2.2)
//void     (*sa_sigaction)(int, siginfo_t *, void *);
int	setup_signals(t_minishell *shell)
{
	struct sigaction	action;
	int					i;

	action = (struct sigaction){0};
	sigemptyset(&action.sa_mask);
	i = -1;
	while (++i < 32)
		sigaction(i, 0, &shell->old_handlers[i]);
	if (shell->interactive_mode)
		signals_interactive(shell, &action);
	else
		signals_non_interactive(shell, &action);
	return (1);
}

int	init_process(t_minishell *shell, char **envp)
{
	ft_bzero(shell, sizeof(t_minishell));
	shell->name = "minishell";
	shell->environment = (void *)ft_arrmap(
			(void *)envp, (void *)ft_strdup, free);
	if (!shell->environment)
		return (-1);
	if (check_stdfds() < 0)
		return (-2);
	init_xvars(shell, &shell->environment);
	shell->interactive_mode = isatty(STDIN_FILENO);
	if (!setup_signals(shell))
		return (-3);
	shell->my_pid = get_my_pid();
	if (shell->my_pid == -1)
		return (-4);
	init_debugger(&shell->info);
	shell->fsm_data.debuginfo = &shell->info;
	reset_for_command(shell, READ_START);
	shell->rldata.interactive_mode = &shell->interactive_mode;
	shell->ulimit_n = get_ulimitn();
	shell->rldata.fsm_data = &shell->fsm_data;
	if (shell->ulimit_n <= 0)
		return (-5);
	return (0);
}
