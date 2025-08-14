/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 00:32:33 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/ft_printf.h"

extern int	g_global_signal;

int	create_tree_and_run(t_minishell *shell)
{
	shell->tokens = fsm_pop_list(&shell->fsm_data);
	dbg_add_token_list(&shell->info, shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	shell->astcode = produce_ast(shell, shell->tokenv, &shell->current_tree);
	if (shell->astcode == AST_ERR_NONE)
	{
		dbg_add_ast(&shell->info, shell->current_tree);
		if (shell->interactive_mode)
			set_exection_signals();
		execute_ast(shell, shell->current_tree);
		if (shell->interactive_mode)
			setup_signals(shell);
	}
	else if (shell->astcode == AST_ERR_SYNTAX)
		ft_fprintf(2, "Parse error: Syntax Error\n");
	else if (shell->astcode == AST_ERR_INVALID_REDIRECT)
		ft_fprintf(2, "Parse error: ambiguous redirect\n");
	return (shell->astcode);
}

// This shouldn't have used a loop, idk what i was thinking,
// we already have a loop in the main function that will do this for us
int	next_command(t_minishell *shell)
{
	shell->rlcode = READ_START;
	shell->rlcode = read_until_complete_command(shell);
	if (shell->rlcode == READ_BADPARSE)
		ft_fprintf(2, "Parse error: %s!\n", shell->fsm_data.str_cond);
	else if (shell->rlcode == READ_EOF)
		return (shell->rlcode);
	else if (shell->rlcode == READ_OK
		&& create_tree_and_run(shell) == AST_ERR_FATAL)
		return (READ_FATAL);
	else if (shell->rlcode == READ_FATAL)
		perror_exit(shell, "readline_loop");
	return (shell->rlcode);
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

// looks like bash sets the return code to 2 in this case
// not sure if i should do the same? 
int	break_case(t_minishell *shell)
{
	if (shell->interactive_mode)
	{
		if (shell->rlcode == READ_EOF)
			return (1);
	}
	else if (!shell->interactive_mode)
	{
		if (shell->rlcode == READ_BADPARSE)
			return (ft_printf("minishell: line %d: Bad Parse\n",
					shell->rldata.lines_read), 1);
		if (shell->astcode == AST_ERR_SYNTAX)
			return (ft_printf("minishell: line %d: Bad Parse\n",
					shell->rldata.lines_read), 1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};

	(void)argc;
	(void)argv;
	if (init_process(&shell, envp) < 0)
		return (0);
	shell.argc = argc;
	shell.argv = argv;
	if (shell.interactive_mode)
		printf("Started with pid: %d\nStarted with seed: %d\n",
			get_my_pid(), ft_rand(0, 100));
	while (1)
	{
		next_command(&shell);
		if (break_case(&shell))
			break ;
		(dbg_write_states(&shell.info), dbg_write_tokens(&shell.info));
		(dbg_write_nodes(&shell.info), dbg_write_end(&shell.info));
		reset_for_command(&shell, shell.rlcode);
	}
	return (free_everything(&shell, 0));
}
