/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:55:51 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/16 13:14:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_global_signal = 0;

void sig_int_handle_interactive(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_global_signal = sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}

/**
 * @brief Will set the global signal to notify that a child process died
 * 
 * @param sig the signal recieved
 * @param info info about the signal
 * @param context context of the signal
 */
void	notify_reap_child(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	g_global_signal = sig;
}

void	default_sig_handle(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_global_signal = sig;
	// kill(-get_my_pid(), sig);
}