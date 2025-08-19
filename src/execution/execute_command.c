/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:36:22 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 21:34:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_raw(t_minishell *shell, t_astnode *node, t_builtincmd cmd)
{
	if (cmd)
		exec_builtincmd(shell, node, cmd);
	else
		get_exec_cmd(shell, node, NULL);
	return (0);
}

int	exec_default(t_minishell *shell, t_astnode *node, t_builtincmd cmd)
{
	pid_t	pid;
	int		returncode;

	if (cmd)
		return (exec_builtincmd(shell, node, cmd));
	pid = fork();
	returncode = -1;
	if (pid == 0)
		get_exec_cmd(shell, node, NULL);
	else if (pid > 0)
		waitpid(pid, &returncode, 0);
	else
		perror_exit(shell, "exec_cmd fork");
	_set_returncode(&shell->return_code, returncode);
	return (0);
}

void	handle_last_argv(t_minishell *shell, char *last_argv)
{
	char	*temp;

	temp = str_vec_join((const char *[3]){"_=", last_argv, 0});
	if (!temp)
		perror_exit(shell, "setting var value");
	else if (set_any_env(shell, &temp, 1) == -1)
	{
		free(temp);
		perror_exit(shell, "setting var value");
	}
	free(temp);
}

int	execute_command(t_minishell *shell, t_astnode *node)
{
	node->cmdv = cmdv_prep(shell, node);
	if (node->cmd_i != (size_t)-1)
	{
		handle_last_argv(shell, node->cmdv[node->argc - 1]);
		if (prepare_fds(shell, node) < 0)
		{
			shell->return_code = 1;
			return (-1);
		}
		if (node->from_type == AST_PIPE)
			exec_raw(shell, node, _get_builtincmd(node));
		else
			exec_default(shell, node, _get_builtincmd(node));
		return (0);
	}
	handle_last_argv(shell, "");
	shell->return_code = 0;
	return (set_any_env(shell, node->cmdv, node->token_count));
}
