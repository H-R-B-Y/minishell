/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:21:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/18 15:44:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"
#include <sys/time.h>
#include <unistd.h>

int	builtin_echo(t_minishell *shell, char **argv, char ***envp)
{
	int		nlflag;
	size_t	idx;

	(void)shell;
	(void)envp;
	if (!argv[1])
		return (printf("\n"), 0);
	nlflag = !ft_strcmp(argv[1], "-n");
	idx = 1;
	while (!ft_strcmp(argv[idx], "-n"))
		idx++;
	while (argv[idx])
	{
		printf("%s", (argv[idx++]));
		if (argv[idx])
			printf(" ");
	}
	printf("%s", (char *[2]){"\n", ""}[nlflag]);
	return (0);
}
