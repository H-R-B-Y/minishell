/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:57:53 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:40:17 by cquinter         ###   ########.fr       */
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
	char	*o_path;
	char	**argv;
	char	*exec_path;

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
