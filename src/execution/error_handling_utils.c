#include "../../include/minishell.h"

// TODO: test. ALso, maybe make a exit_message genral function to print and exit, success and failure
void	perror_exit(t_minishell *shell, char *message)
{
	perror(message);
	reset_for_command(shell);
	fflush(stdout);
	free(shell->prompt);
	ft_arrclear((void *)shell->environment, free);
	restore_signals(shell);
	exit(EXIT_FAILURE);
}