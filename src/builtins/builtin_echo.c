/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:21:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/13 15:17:42 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

#include <sys/time.h>
#include <unistd.h>

// static int	output_writable(void)
// {
// 	struct stat	s;

// 	ft_bzero(s, sizeof(struct stat));
// 	if (fstat(STDOUT_FILENO, &s) < 0)
// 		return (-1);
// 	return (0);
// }

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
	if (nlflag)
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

