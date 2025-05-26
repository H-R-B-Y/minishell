/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:10:47 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/26 16:54:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_pwd(t_minishell *shell, char **argv, char **envp)
{
	char	*pwd;

	(void)shell;
	(void)argv;
	(void)envp;
	pwd = getcwd(0, 0);
	if (!pwd)
		return (perror("pwd"), free(pwd), 1);
	else
		return (printf("%s\n", pwd), free(pwd), 0);
}
