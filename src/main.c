/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 16:07:37 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

int main()
{
	t_minishell	shell;

	ft_bzero(&shell, sizeof(t_minishell));
	add_history("(this\n) && should work");
	add_history("\"this\n should\"\nwork");
	shell.prompt = "minishell -> ";
	while (!readline_loop(&shell))
	{
		print_token_list(shell.tokens);
		shell.tokenv = (void *)ft_lstarr(shell.tokens);
		ft_lstclear(&shell.tokens, 0); // we free all the list items but not the list content as that is still in use.
		shell.current_tree = produce_ast(shell.tokenv, ft_arrlen((void *)shell.tokenv));
		print_ast(shell.current_tree, "|	|");
		add_history(shell.current_line);
	}
	return (0);
}