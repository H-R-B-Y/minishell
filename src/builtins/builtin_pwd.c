/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:10:47 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/29 11:46:28 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_pwd(t_minishell *shell, char **argv, char ***envp)
{
	char	*pwd;

	(void)shell;
	(void)argv;
	(void)envp;
	pwd = getcwd(0, 0);
	if (!pwd)
		return (perror("minishell: pwd"), free(pwd), 1);
	else
		return (printf("%s\n", pwd), free(pwd), 0);
}
