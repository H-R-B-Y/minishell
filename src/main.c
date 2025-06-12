/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/12 18:01:41 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_global_signal;

int	prep_tree(t_minishell *shell)
{
	t_asterror	astcode;

	shell->tokens = fsm_pop_list(&shell->fsm_data);
	print_token_list(shell->tokens);
	dbg_add_token_list(shell->tokens);
	shell->tokenv = (void *)ft_lstarr(shell->tokens);
	ft_lstclear(&shell->tokens, 0);
	astcode = produce_ast(shell, shell->tokenv, &shell->current_tree);
	if (astcode == AST_ERR_NONE)
	{
		print_ast(shell->current_tree, "|	|");
		dbg_add_ast(shell->current_tree);
		execute_ast(shell);
	}
	else if (astcode == AST_ERR_SYNTAX)
		printf("Parse error: Syntax Error\n");
	return (astcode);
}

int	next_command(t_minishell *shell)
{
	t_readline_retcode	rlcode;
	

	rlcode = read_until_complete_command(shell);
	if (rlcode == READ_OK)
		prep_tree(shell);
	else if (rlcode == READ_BADPARSE)
		printf("Parse error: %s!\n", shell->fsm_data.str_condition);
	else if (rlcode == READ_ERROR)
		printf("Issue encountered while reading!\n"); // should probably collect some data to provide the user when this happens
	else if (rlcode == READ_EOF)
		return (rlcode);
	return (rlcode);
}

pid_t	get_my_pid();
int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};

	(void)argc;
	(void)argv;
	init_process(&shell, envp);
	printf("Started with pid: %d\n", get_my_pid());
	while (1)
	{
		if (next_command(&shell) == READ_EOF)
			break ;
		dbg_write_states(static_debug_info());
		dbg_write_tokens(static_debug_info());
		dbg_write_nodes(static_debug_info());
		dbg_write_end(static_debug_info());
		reset_for_command(&shell);
	}
	reset_for_command(&shell);
	printf("freeing prompt: \n");
	fflush(stdout);
	free(shell.prompt);
	ft_arrclear((void *)shell.environment, free);
	return (0);
}
