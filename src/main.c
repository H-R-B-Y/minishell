/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/01 19:22:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clear_screen(void)
{
	printf("\033[2J\033[H");
	fflush(stdout);
}

void	print_token_list(t_list *list)
{
	t_list *next;

	next = list;
	while (next)
	{
		print_token(next->content, 25);
		next = next->next;
	}
}

void readline_loop(void)
{
	char	*buff;
	t_list	*tokens;
	
	static char *arr[2] = {"not ", ""}; //TODO: remove this 

	buff = readline("minishell-$ ");
	while (buff)
	{
		if (*buff) add_history(buff);
		if (!strcmp("clear", buff))
			ft_clear_screen();
		else
		{
			tokens = tokenise(buff);
			int valid = cleanse_validate_tokens(tokens);
			print_token_list(tokens);
			printf("tokens are %svalid\n", arr[valid]);
		}
		free(buff);
		buff = readline("minishell-$ ");
	}
}

int main()
{
	readline_loop();
	return (0);
}