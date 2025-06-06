/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:48:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/06 16:17:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void sig_int_handle_interactive(int sig, siginfo_t *info, void *context);

void	warning_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	printf("Warning signal handler for signal %d not written yet\n", sig); // note signals should NOT print

}

int	event(void)
{
	return (0);
}

int	signals_interactive(t_minishell *shell, struct sigaction *act)
{
	// SIGINT = clear prompt, newline, clean start, do not add too history
	act->sa_sigaction = sig_int_handle_interactive;
	sigaction(SIGINT, act, &shell->old_sigint);
	// SIGQUIT = do nothing (ignore)
	act->sa_sigaction = warning_handler;
	sigaction(SIGQUIT, act, &shell->old_sigquit);
	// any others?
	rl_event_hook = event;
	return (0);
}

int signals_non_interactive(t_minishell *shell, struct sigaction *act)
{
	// idk if signals are actually needed here
	(void)shell;
	(void)act;
	return (0);
}


//       SA_SIGINFO (since Linux 2.2)
//void     (*sa_sigaction)(int, siginfo_t *, void *);
int	setup_signals(t_minishell *shell)
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags |= SA_SIGINFO;
	if (shell->interactive_mode)
		signals_interactive(shell, &action);
	else
		signals_non_interactive(shell, &action);
	return (1);
}


int	init_process(t_minishell *shell, char **envp)
{
	ft_bzero(shell, sizeof(t_minishell));
	shell->environment = (void *)ft_arrmap((void *)envp, (void *)ft_strdup, free);
	if (!shell->environment)
		return (-1);
	// check pty
	shell->interactive_mode = isatty(STDIN_FILENO);
	// setup signal handlers
	if (!setup_signals(shell))
		return (-2);
	// init debugger
	if (!init_debugger(&shell->info))
		printf("debugger not enabled: %s\n", strerror(errno));
	// reset for command
	reset_for_command(shell);
	return (0);
}
