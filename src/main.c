/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/22 18:47:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;(void)argv;
	shell.environment = envp;
	ft_bzero(&shell, sizeof(t_minishell));
	reset_fsm(&shell.fsm_data);
	add_history("(this\n) && should work");
	add_history("\"this\n should\"\nwork");
	add_history("(this &&\nhas a seperator)");
	shell.prompt = "minishell -> ";
	while (!readline_loop(&shell))
	{
		if (shell.fsm_data.state != PARSE_ERROR)
		{
			print_token_list(shell.tokens);
			shell.tokenv = (void *)ft_lstarr(shell.tokens);
			ft_lstclear(&shell.tokens, 0);
			shell.current_tree = produce_ast(shell.tokenv,
				ft_arrlen((void *)shell.tokenv));
			print_ast(shell.current_tree, "|	|");
			add_history(shell.current_line);
		}
		reset_fsm(&shell.fsm_data);
	}
	reset_fsm(&shell.fsm_data);
	return (0);
}