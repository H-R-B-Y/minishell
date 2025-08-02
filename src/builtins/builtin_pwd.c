/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:10:47 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/02 18:35:30 by cquinter         ###   ########.fr       */
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
		return (perror("minishell: pwd"), 1);
	else
		return (printf("%s\n", pwd), free(pwd), 0);
}
