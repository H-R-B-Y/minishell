/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:48:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/06 13:39:29 by cquinter         ###   ########.fr       */
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
	// SIGQUIT = do nothing (ignore)	;
	(void)shell;
	act->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, act, 0);
	sigaction(SIGTSTP, act, 0);
	act->sa_flags |= SA_SIGINFO;
	act->sa_flags |= SA_RESTART;
	act->sa_handler = 0;
	act->sa_sigaction = sig_int_handle_interactive;
	sigaction(SIGINT, act, 0);
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
	shell->environment = (void *)ft_arrmap((void *)envp, (void *)ft_strdup, free);
	if (!shell->environment)
		return (-1);
	// check pty
	shell->interactive_mode = isatty(STDIN_FILENO);
	// setup signal handlers
	if (!setup_signals(shell))
		return (-2);
	shell->my_pid = get_my_pid();
	if (shell->my_pid == -1)
		return (-3);
	// init debugger
	if (!init_debugger(&shell->info))
		printf("debugger not enabled: %s\n", strerror(errno));
	shell->fsm_data.debuginfo = &shell->info;
	// reset for command
	reset_for_command(shell);
	return (0);
}
