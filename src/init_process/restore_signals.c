/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 18:49:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_signals(const t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		sigaction(i, &shell->old_handlers[i], 0);
		i++;
	}
}

void	set_exection_signals(void)
{
	struct sigaction	p;

	ft_bzero(&p, sizeof(p));
	sigemptyset(&p.sa_mask);
	p.sa_flags |= SA_SIGINFO;
	p.sa_flags |= SA_RESTART;
	p.sa_sigaction = default_sig_handle;
	sigaction(SIGINT, &p, 0);
	sigaction(SIGQUIT, &p, 0);
}
