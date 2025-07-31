#include "../../include/minishell.h"
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

void	exec_errno_handling(t_minishell *shell, char *path)
{
	struct stat	statbuf;

	ft_memset(&statbuf, 0, sizeof(statbuf));
	if (errno == ENOENT)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_exit_status(shell, 127);
	}
	else if (errno == EACCES && stat(path, &statbuf) == 0 
		&& S_ISDIR(statbuf.st_mode))
		errno = EISDIR;
	perror_exit(shell, path);
}

void	get_exec_cmd(t_minishell *shell, t_astnode *node, t_builtincmd *b_in)
{
	char		*path;
	char		**argv;
	char		*exec_path = NULL;
	
	(void)b_in;
	node->envp = (char **)ft_arrmap((void **)shell->environment,
		(void *)ft_strdup, free);
	if (!node->envp)
		perror_exit(shell, "ft_arrmap");
	path = node->cmdv[node->cmd_i];
	argv = node->cmdv + node->cmd_i;
	restore_signals(shell);
	map_fds(node);
	errno = 0;
	if (ft_strchr(path, '/'))
		execve(path, argv, node->envp);
	else
		exec_path = get_exec_path(shell, path, node->envp);
	if (exec_path)
	{
		execve(exec_path, argv, node->envp);
		free(exec_path);
	}
	exec_errno_handling(shell, path);
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

int	execute_command(t_minishell *shell, t_astnode *node)
{
	node->cmdv = cmdv_prep(shell, node); // pending: shorten remove quotes and clean up in case of error
	glob_variable(node);
	if (prepare_fds(node) < 0)
		return (-1);
	if (node->cmd_i != (size_t)-1)
	{
		if (node->from_type == AST_PIPE)
			exec_raw(shell, node, _get_builtincmd(node));
		else
			exec_default(shell, node, _get_builtincmd(node));
		return (0);
	}
	return (set_any_env(shell, node->cmdv, node->token_count));
}
