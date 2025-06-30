
#include "../../include/minishell.h"

void	_write_pipe(t_minishell *shell, t_astnode *node, int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror_exit(shell, "minishell: pipe dup2");
	close(fd[1]);
	close(fd[0]);
	node->from_type = AST_PIPE;
	execute_ast(shell, node);
	builtin_exit(shell, NULL, NULL);
}

void	_read_pipe(t_minishell *shell, t_astnode *node, int *fd)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror_exit(shell, "minishell: pipe dup2");
	close(fd[1]);
	close(fd[0]);
	node->from_type = AST_PIPE;
	execute_ast(shell, node);
	builtin_exit(shell, NULL, NULL);
}

int	execute_pipe(t_minishell *shell, t_astnode *node)
{
	int		fd[2];
	pid_t	pid_w;
	pid_t	pid_r;
	int		returncode;

	if (pipe(fd) == -1)
		perror_exit(shell, "minishell: pipe");
	returncode = -1;
	pid_w = fork();
	if (pid_w == -1)
		perror_exit(shell, "minishell: pipe fork");
	if (pid_w == 0)
		_write_pipe(shell, node->left_node, fd);
	pid_r = fork();
	if (pid_r == -1)
		perror_exit(shell, "minishell: pipe fork");
	if (pid_r == 0)
		_read_pipe(shell, node->right_node, fd);
	close(fd[0]);	
	close(fd[1]);
	waitpid(pid_w, NULL, 0);
	waitpid(pid_r, &returncode, 0);
	_set_returncode(&shell->return_code, returncode);
	return (0);
}
