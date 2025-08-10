/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:36:22 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/09 21:44:37 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

void	exec_errno_handling(t_minishell *shell, char *path)
{
	struct stat	statbuf;
	int			st;

	ft_memset(&statbuf, 0, sizeof(statbuf));
	st = stat(path, &statbuf);
	if (errno == ENOENT)
	{
		ft_fprintf(2, "\'%s\'", path);
		ft_putstr_fd(": command not found\n", 2);
		clean_exit_status(shell, 127);
	}
	else if (errno == EACCES && st == 0
		&& S_ISDIR(statbuf.st_mode))
		errno = EISDIR;
	perror_exit(shell, path);
}

void	get_exec_cmd(t_minishell *shell, t_astnode *node, t_builtincmd b_in)
{
	char		*o_path;
	char		**argv;
	char		*exec_path = NULL;
	
	(void)b_in;
	o_path = node->cmdv[node->cmd_i];
	node->cmd_path = o_path;
	argv = node->cmdv + node->cmd_i;
	set_cmd_envp(shell, node, b_in);
	restore_signals(shell);
	if (map_fds(node) < 0)
		clean_exit_status(shell, 1);
	errno = 0;
	if (!ft_strchr(o_path, '/'))
		exec_path = get_exec_path(shell, o_path, node->envp);
	if (exec_path)
		node->cmd_path = exec_path;
	_set_var_value(shell, node->cmd_path, "_", &node->envp);
	execve(node->cmd_path, argv, node->envp);
	exec_errno_handling(shell, o_path);
}

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
		return(exec_builtincmd(shell, node, cmd));
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
		free(temp), perror_exit(shell, "setting var value");
	free(temp);
}

int	execute_command(t_minishell *shell, t_astnode *node)
{
	node->cmdv = cmdv_prep(shell, node); // pending: shorten remove quotes and clean up in case of error
	glob_variable(node);
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
	return (set_any_env(shell, node->cmdv, node->token_count));
}
