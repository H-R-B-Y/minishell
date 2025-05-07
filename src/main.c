/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/07 10:23:02 by hbreeze          ###   ########.fr       */
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

// void readline_loop(void)
// {
// 	char	*buff;
// 	t_list	*tokens;
// 	t_token	**tok_arr;
// 	t_astnode	*tree;
	
// 	static char *arr[2] = {"", "not "}; //TODO: remove this 

// 	buff = readline("minishell-$ ");
// 	while (buff)
// 	{
// 		if (*buff) add_history(buff);
// 		if (!strcmp("clear", buff))
// 			ft_clear_screen();
// 		else
// 		{
// 			tokens = tokenise(buff);
// 			int valid = cleanse_validate_tokens(tokens);
// 			if (valid)
// 				{print_token_error(valid);printf("\n");}
// 			print_token_list(tokens);
// 			printf("tokens are %svalid\n", arr[!!valid]);
// 			// produce ast
// 			tok_arr = (void *)ft_lstarr(tokens);
// 			tree = produce_ast(tok_arr, ft_arrlen((void *)tok_arr));
// 			print_ast(tree, "|	|");
// 		}
// 		free(buff);
// 		buff = readline("minishell-$ ");
// 	}
// }

int main()
{
	t_minishell	shell;

	add_history("(this\n) && should work");
	add_history("\"this\n should\"\nwork");
	shell.prompt = "minishell -> ";
	readline_loop(&shell);
	return (0);
}