/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/14 18:30:07 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}
	// while (!readline_loop(&shell))
	// {
	// 	if (shell.tok_internal.state == PARSE_ERROR)
	// 		continue ;
	// 	print_token_list(shell.tokens);
	// 	shell.tokenv = (void *)ft_lstarr(shell.tokens);
	// 	ft_lstclear(&shell.tokens, 0);
	// 	// we free all the list items but not
	// 	// 	the list content as that is still in use.
	// 	shell.current_tree = produce_ast(shell.tokenv,
	// 		ft_arrlen((void *)shell.tokenv));
	// 	print_ast(shell.current_tree, "|	|");
	// 	add_history(shell.current_line);
	// }
	// return (0);


int main()
{
	t_minishell	shell;

	ft_bzero(&shell, sizeof(t_minishell));
	// add_history("(this\n) && should work");
	// add_history("\"this\n should\"\nwork");
	// add_history("(this &&\nhas a seperator)");
	shell.prompt = "minishell -> ";
	while (1)
	{
		char *line = readline(shell.prompt);
		if (!line)
			break ;
		t_tokretcode rc = tokenise(line);
		printf("Retcode %s\n", tokretcode_str(rc));
		if (rc == PARSE_OK)
			print_token_list(fsm()->tokens);
		if (rc != PARSE_CONT)
			reset_fsm();
	}
	reset_fsm();
}