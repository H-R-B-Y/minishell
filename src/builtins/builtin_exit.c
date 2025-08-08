/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/06 17:24:55 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

static int	is_alldigit(char *str)
{
	if(!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(t_minishell *shell, char **argv, char ***envp)
{
	int	status;
	size_t	argc;

	(void)envp;
	printf("exit\n");
	status = shell->return_code;
	argc = ft_arrlen((void **)argv);
	if (argc > 1 && !is_alldigit(argv[1]))
	{
		status = 2;
		ft_fprintf(2, "%s: exit: %s: numeric argument required\n",
			shell->name, argv[1]);
	}
	else if (argc > 2)
		return (ft_fprintf(2, "%s: exit: too many arguments\n", shell->name), 
			EXIT_FAILURE);
	else if (argc == 2)
		status = ft_atoi(argv[1]);
	clean_shell(shell);
	exit(status);
}
