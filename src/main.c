/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 14:14:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

void	freetokenv(t_token **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		destroy_token(tokens[i++], free);
	free(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.environment = ft_arrmap((void *)envp, ft_strdup, free);
	if (!shell.environment)
		return (perror("minishell: malloc:"), 1);
	ft_bzero(&shell, sizeof(t_minishell));
	add_history("(this\n) && should work");
	add_history("\"this\n should\"\nwork");
	add_history("(this &&\nhas a seperator)");
	shell.prompt = "minishell -> ";
	reset_fsm(&shell.fsm_data);
	while (!readline_loop(&shell))
	{
		print_token_list(shell.tokens);
		shell.tokenv = (void *)ft_lstarr(shell.tokens);
		ft_lstclear(&shell.tokens, 0);
		shell.current_tree = produce_ast(shell.tokenv,
				ft_arrlen((void *)shell.tokenv));
		print_ast(shell.current_tree, "|	|");
		add_history(shell.current_line);
		reset_fsm(&shell.fsm_data);
		freetokenv(shell.tokenv);
	}
	readline_cleanup(&shell);
	destroy_ast(&shell.current_tree);
	reset_fsm(&shell.fsm_data);
	return (0);
}
