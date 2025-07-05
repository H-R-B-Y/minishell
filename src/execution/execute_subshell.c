
#include "../../include/minishell.h"

int	execute_subshell(t_minishell *shell, t_astnode *node)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execute_ast(shell, node->left_node);
		exit(shell->return_code);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror_exit(shell, "minishell: subshell");
	_set_returncode(&shell->return_code, status);
	return (shell->return_code);
}
