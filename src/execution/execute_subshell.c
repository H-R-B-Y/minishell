
#include "../../include/minishell.h"

int	execute_subshell(t_minishell *shell, t_astnode *node)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		// Note that subshells can be owners of redirects, 
		// the node will need to have its redircts mapped BEFORE calling the rest of the
		// ast? maybe (i have not tested if the subshell redirects get overridden by the
		// child nodes redirects)
		execute_ast(shell, node->left_node);
		exit(free_everything(shell, 0));
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror_exit(shell, "subshell");
	_set_returncode(&shell->return_code, status);
	return (shell->return_code);
}
