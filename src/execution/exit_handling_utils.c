#include "../../include/minishell.h"

// TODO: test. ALso, maybe make a exit_message genral function to print and exit, success and failure
void	perror_exit(t_minishell *shell, char *message)
{
	perror(message);
	reset_for_command(shell, READ_NOTHING);
	fflush(stdout);
	free(shell->prompt);
	ft_arrclear((void *)shell->environment, free);
	restore_signals(shell);
	exit(EXIT_FAILURE);
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