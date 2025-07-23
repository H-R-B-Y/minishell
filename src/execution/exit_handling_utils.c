#include "../../include/minishell.h"

void	clean_shell(t_minishell *shell)
{
	reset_for_command(shell, READ_NOTHING);
	fflush(stdout);
	free(shell->prompt);
	ft_arrclear((void *)shell->environment, free);
	restore_signals(shell);
}

void	clean_exit_status(t_minishell *shell, int status)
{
	clean_shell(shell);
	exit(status);
}

// TODO: test. ALso, maybe make a exit_message genral function to print and exit, success and failure
void	perror_exit(t_minishell *shell, char *message)
{
	perror(message);
	clean_exit_status(shell, EXIT_FAILURE);
}

void	_set_returncode(int *to_set, int code)
{
	if (WIFEXITED(code))
		*to_set = WEXITSTATUS(code);
	else if (WIFSIGNALED(code))
		*to_set = 128 + WTERMSIG(code);
	else
		*to_set = 1;
}
