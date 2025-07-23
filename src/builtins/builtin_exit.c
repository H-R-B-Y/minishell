/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/23 18:00:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_exit(t_minishell *shell, char **argv, char ***envp)
{
	int	status;
	size_t	argc;

	(void)envp;
	printf("exit\n");
	argc = ft_arrlen((void **)argv);
	if (argc > 2)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 
			EXIT_FAILURE);
	else if (argc == 2)
		status = ft_atoi(argv[1]);
	// if (*envp)
	// 	ft_arrclear((void **)(*envp), free);
	// if (argv)
	// 	ft_arrclear((void **)argv, free);
	clean_shell(shell);
	if (argc == 2)
		exit(status);
	else
		exit(42);
}
