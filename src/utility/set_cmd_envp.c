/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:59:58 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/05 15:06:50 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_cmd_envp(t_minishell *shell, t_astnode *node, t_builtincmd b_in)
{
	if (b_in)
	{
		if (set_n_envp(&node->envp, node->cmdv, node->cmd_i) == -1)
			perror_exit(shell, "setting b_in cmd envp");
	}
	else
	{
		node->envp = (char **)ft_arrmap((void **)shell->environment,
			(void *)ft_strdup, free);
		if (!node->envp)
			perror_exit(shell, "ft_arrmap");
		if (set_n_envp(&node->envp, node->cmdv, node->cmd_i) == -1)
			perror_exit(shell, "setting cmd envp");
	}
}
