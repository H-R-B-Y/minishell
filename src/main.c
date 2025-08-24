/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/24 16:33:32 by hbreeze          ###   ########.fr       */
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
	else if (g_global_signal)
		shell->return_code = 128 + g_global_signal;
	return (shell->astcode);
}

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
	else if (shell->rlcode != READ_OK && g_global_signal)
		shell->return_code = g_global_signal + 128;
	return (shell->rlcode);
}

int	break_case(t_minishell *shell)
{
	if (shell->interactive_mode)
	{
		if (shell->rlcode == READ_EOF)
			return (ft_fprintf(2, "exit\n"), 1);
	}
	if (!shell->interactive_mode)
	{
		if (shell->rlcode == READ_BADPARSE || shell->astcode == AST_ERR_SYNTAX)
		{
			ft_printf("minishell: line %d: Bad Parse\n",
				shell->rldata.lines_read);
			clean_exit_status(shell, 2);
		}
		if (shell->rlcode == READ_EOF)
			return (1);
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
		printf("Started with pid: %d, %ld\n", get_my_pid(), shell.ulimit_n);
	while (1)
	{
		next_command(&shell);
		(dbg_write_states(&shell.info), dbg_write_tokens(&shell.info));
		(dbg_write_nodes(&shell.info), dbg_write_end(&shell.info));
		if (break_case(&shell))
			break ;
		reset_for_command(&shell, shell.rlcode);
	}
	clean_exit_status(&shell, shell.return_code);
}
