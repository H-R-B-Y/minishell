/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/04/30 19:03:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}
void readline_loop(void)
{
	char	*buff;

	buff = readline("minishell-$ ");
	while (buff)
	{
		if (*buff) add_history(buff);
		printf("%s\n", buff);
		if (!strcmp("clear", buff))
			ft_clear_screen();
		free(buff);
		buff = readline("minishell-$ ");
	}
}

int main()
{
	readline_loop();
	return (0);
}