/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/08 14:12:52 by hbreeze          ###   ########.fr       */
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
		;
	return (0);
}