/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:47:53 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 18:28:47 by hbreeze          ###   ########.fr       */
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

int	better_add_history(char *string)
{
	size_t		i;
	HIST_ENTRY	**the_history;
	int			ret;

	the_history = history_list();
	i = 0;
	ret = 1;
	while (the_history[i])
	{
		if (!ft_strncmp(the_history[i]->line, string,
			ft_strlen(the_history[i]->line) + 1))
		{
			ret = 0;
			remove_history((int)i);
			break ;
		}
		i++;
	}
	add_history(string);
	return (ret);
}

void	reset_for_command(t_minishell *shell)
{
	if (shell->rldata.current_hist_item)
	{
		better_add_history(shell->rldata.current_hist_item);
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

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell = {0};
	t_readline_retcode	rlcode;

	(void)argc;
	(void)argv;
	shell.environment = envp;
	reset_for_command(&shell);
	signal(SIGINT, do_something);
	add_history("(this\n) && should work"); add_history("\"this\n should\"\nwork"); add_history("(this &&\nhas a seperator)");
	shell.prompt = "minishell -> ";
	printf("%s\n\n", remove_quotes("\"this\"\"text\""));
	while (1)
	{
		rlcode = read_until_complete_command(&shell);
		if (rlcode == READ_OK)
		{
			shell.tokens = fsm_pop_list(&shell.fsm_data);
			print_token_list(shell.tokens);
			shell.tokenv = (void *)ft_lstarr(shell.tokens);
			ft_lstclear(&shell.tokens, 0);
			shell.current_tree = produce_ast(&shell, shell.tokenv,
				ft_arrlen((void *)shell.tokenv));
			print_ast(shell.current_tree, "|	|");
		}
		else if (rlcode == READ_BADPARSE)
			printf("Parse error: %s!\n", shell.fsm_data.str_condition);
		else if (rlcode == READ_ERROR)
			printf("Issue encountered while reading!\n"); // should probably collect some data to provide the user when this happens
		else if (rlcode == READ_EOF)
			break ;
		reset_for_command(&shell);
	}
	// readline_cleanup(&shell);
	destroy_ast(&shell.current_tree);
	reset_fsm(&shell.fsm_data);
	return (0);
}
