/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:36:42 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/08 17:03:43 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	execute_subshell(t_minishell *shell, t_astnode *node)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (prepare_fds(shell, node) < 0)
			clean_exit_status(shell, 2);
		if (map_fds(node) < 0)
			clean_exit_status(shell, 1);
		execute_ast(shell, node->left_node);
		clean_exit_status(shell, shell->return_code);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror_exit(shell, "subshell");
	_set_returncode(&shell->return_code, status);
	return (shell->return_code);
}
