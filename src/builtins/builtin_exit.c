/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/29 14:32:35 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

static void	warning_message(void)
{
	printf("entire process cleanup has not been ");
	printf("implemented yet, memory leaks will occur here\n");
}

/*
Probably not a good idea to allow memory leaks here, but in fairness
bash leaks here so idk.

I will attempt to cleanup here though, just in case.
*/
// think it would be good to accept a status code from input here.
int	builtin_exit(t_minishell *shell, char **argv, char ***envp)
{
	(void)shell;
	(void)argv;
	(void)envp;
	warning_message();

	// reset_for_command(shell);
	// fflush(stdout);
	// free(shell->prompt);
	// ft_arrclear((void *)shell->environment, free);
	// restore_signals(shell);

	printf("exit\n");
	exit(42);
}
