/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:21:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/26 15:42:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

void	*print_and_ret(void *p);

int	builtin_echo(t_minishell *shell, char **argv, char **envp)
{
	int		nlflag;

	(void)shell;
	(void)envp;
	if (!argv[1])
		return (0);
	nlflag = !ft_strcmp(argv[1], "-n");
	ft_arriter((void *)argv + nlflag, print_and_ret);
	printf("%s", (char *[2]){"", "\n"}[nlflag]);
	return (0);
}
