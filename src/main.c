/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/09 21:14:44 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_global_signal;

int	prep_tree(t_minishell *shell)
{
	t_asterror	astcode;

	shell->tokens = fsm_pop_list(&shell->fsm_data);
	// print_token_list(shell->tokens);4az
	dbg_add_token_list(&shell->info, shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	astcode = produce_ast(shell, shell->tokenv, &shell->current_tree);
	if (astcode == AST_ERR_NONE)
	{
		// print_ast(shell->current_tree, "|	|");
		dbg_add_ast(&shell->info, shell->current_tree);
		if (shell->interactive_mode)
			set_exection_signals();
		execute_ast(shell, shell->current_tree);
		setup_signals(shell);
	}
	else if (astcode == AST_ERR_SYNTAX)
		printf("Parse error: Syntax Error\n");
	return (astcode);
}

int	next_command(t_minishell *shell)
{
	t_readline_retcode	rl_code;
	
	rl_code = READ_START;
	while (rl_code != READ_NOTHING)
	{
		rl_code = read_until_complete_command(shell);
		if (rl_code == READ_OK)
			prep_tree(shell);
		else if (rl_code == READ_BADPARSE)
			printf("Parse error: %s!\n", shell->fsm_data.str_condition);
		else if (rl_code == READ_ERROR)
			printf("Issue encountered while reading!\n"); // should probably collect some data to provide the user when this happens
		else if (rl_code == READ_EOF)
			return (rl_code);
		reset_for_command(shell, rl_code);
	}
	return (rl_code);
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};
	t_readline_retcode	rl_code;

	(void)argc;
	(void)argv;
	init_process(&shell, envp);
	printf("Started with pid: %d\nStarted with seed: %d\n", get_my_pid(), ft_rand(0, 100));
	while (1)
	{
		// printf("\nENV*********************************************************\n\n");
		// ft_arriter((void *)shell.environment, print_and_ret);
		// printf("\nUNASSIGNED*********************************************************\n\n");
		// ft_arriter((void *)shell.unassigned_env, print_and_ret);
		// printf("\nLOCAL*********************************************************\n\n");
		// ft_arriter((void *)shell.local_env, print_and_ret);
		rl_code = next_command(&shell);
		if (rl_code == READ_EOF)
			break ;
		dbg_write_states(&shell.info);
		dbg_write_tokens(&shell.info);
		dbg_write_nodes(&shell.info);
		dbg_write_end(&shell.info);
		reset_for_command(&shell, rl_code);
	}
	reset_for_command(&shell, READ_NOTHING);
	fflush(stdout);
	free(shell.prompt);
	ft_arrclear((void *)shell.environment, free);
	restore_signals(&shell);
	return (0);
}
