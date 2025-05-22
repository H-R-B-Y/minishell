/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:34:33 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 15:46:39 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int	builtin_env(t_minishell *shell, char **argv, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	i = 0;
	while (shell->local_env[i])
		printf("%s\n", envp[i++]);
	return (0);
}
