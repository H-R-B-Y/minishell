/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 12:34:22 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ft_printf.h"

extern int	g_global_signal;

int	create_tree_and_run(t_minishell *shell)
{
	t_asterror	astcode;

	shell->tokens = fsm_pop_list(&shell->fsm_data);
	dbg_add_token_list(&shell->info, shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	astcode = produce_ast(shell, shell->tokenv, &shell->current_tree);
	if (astcode == AST_ERR_NONE)
	{
		dbg_add_ast(&shell->info, shell->current_tree);
		if (shell->interactive_mode)
			set_exection_signals();
		execute_ast(shell, shell->current_tree);
		if (shell->interactive_mode)
			setup_signals(shell);
	}
	else if (astcode == AST_ERR_SYNTAX)
		ft_fprintf(2, "Parse error: Syntax Error\n");
	else if (astcode == AST_ERR_INVALID_REDIRECT)
		ft_fprintf(2, "Parse error: ambiguous redirect\n");
	return (astcode);
}

// This shouldn't have used a loop, idk what i was thinking,
// we already have a loop in the main function that will do this for us
int	next_command(t_minishell *shell)
{
	t_readline_retcode	rl_code;

	rl_code = READ_START;
	rl_code = read_until_complete_command(shell);
	if (rl_code == READ_BADPARSE)
		ft_fprintf(2, "Parse error: %s!\n", shell->fsm_data.str_cond);
	else if (rl_code == READ_ERROR)
		return (rl_code);
	else if (rl_code == READ_EOF)
		return (rl_code);
	else if (rl_code == READ_OK
		&& create_tree_and_run(shell) == AST_ERR_FATAL)
		return (READ_FATAL);
	else if (rl_code == READ_FATAL)
		perror_exit(shell, "readline_loop");
	return (rl_code);
}

int	free_everything(t_minishell *shell, int code)
{
	return (
		reset_for_command(shell, READ_NOTHING),
		fflush(stdout),
		free(shell->prompt),
		ft_arrclear((void *)shell->environment,
			free),
		restore_signals(shell),
		rl_clear_history(),
		code
	);
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};
	t_readline_retcode	rl_code;

	(void)argc;
	(void)argv;
	init_process(&shell, envp);
	shell.argc = argc;
	shell.argv = argv;
	if (shell.interactive_mode)
		printf("Started with pid: %d\nStarted with seed: %d\n",
			get_my_pid(), ft_rand(0, 100));
	while (1)
	{
		rl_code = next_command(&shell);
		if (rl_code == READ_EOF)
			break ;
		(dbg_write_states(&shell.info), dbg_write_tokens(&shell.info));
		(dbg_write_nodes(&shell.info), dbg_write_end(&shell.info));
		reset_for_command(&shell, rl_code);
	}
	return (free_everything(&shell, 0));
}
