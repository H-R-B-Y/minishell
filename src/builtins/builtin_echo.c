/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:21:44 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 13:34:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_echo(t_minishell *shell, char **argv, char **envp)
{
	int		nlflag;
	size_t	i;

	if (!argv[1])
		return (0);
	nlflag = !ft_strcmp(argv[1], "-n");
	i = nlflag;
	while (argv[++i])
		printf("%s%s", argv[i], (char *[2]){"", " "}[!!argv[i + 1]]);
	if (!nlflag)
		printf("\n");
	return (0);
}
