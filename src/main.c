/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/16 18:00:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

void do_something(int n)
{
	(void)n;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	reset_for_command(t_minishell *shell)
{
	if (shell->rldata.current_hist_item)
	{
		add_history(shell->rldata.current_hist_item);
		free(shell->rldata.current_hist_item);
		shell->rldata.current_hist_item = 0;
	}
	if (shell->rldata.extra_lines)
	{
		ft_arrclear((void *)shell->rldata.extra_lines, free);
		shell->rldata.extra_lines = 0;
		shell->rldata.extra_line_count = 0;
	}
	reset_fsm(&shell->fsm_data);
}

int main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};

	(void)argc;(void)argv;
	shell.environment = envp;
	reset_for_command(&shell);
	// just some test items
	// signal(SIGUSR1, (void *)do_something);
	add_history("(this\n) && should work"); add_history("\"this\n should\"\nwork"); add_history("(this &&\nhas a seperator)");
	shell.prompt = "minishell -> ";
	while (1)
	{
		if (read_until_complete_command(&shell))
		{
			shell.tokens = fsm_pop_list(&shell.fsm_data);
			print_token_list(shell.tokens);
			shell.tokenv = (void *)ft_lstarr(shell.tokens);
			ft_lstclear(&shell.tokens, 0);
			shell.current_tree = produce_ast(shell.tokenv, ft_arrlen((void *)shell.tokenv));
			print_ast(shell.current_tree, "|	|");
		}
		else
			printf("issue occured!\n");
		reset_for_command(&shell);
	}
	reset_fsm(&shell.fsm_data);
	return (0);
}
