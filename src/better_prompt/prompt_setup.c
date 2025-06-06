/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:46:41 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/06 16:29:00 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_git_dir(void);
int		has_git(void);
char	*run_git_command(char **argv);

size_t	get_terminal_width(void)
{
	struct winsize	ws;
	
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
		return (-1);
	return (ws.ws_col);
}

void clear_previous_prompt(int lns)
{
	int i;

	i=0;
	while (i < lns)
	{
		printf("\033[F");       // move cursor up
		printf("\033[2K\r");    // clear entire line
		i++;
	}
}

char	*prepend_statuscode(t_minishell *shell, char *current)
{
	char *temp[2];
	char *output;

	if (shell->return_code != 0)
		temp[0] = ft_strdup("\033[38;2;255;0;0m");
	else
		temp[0] = ft_strdup("\033[38;2;0;255;0m");
	temp[1] = ft_itoa(shell->return_code);
	output = str_vec_join(
		(char *[6]){
			temp[0],
			" ",temp[1]," ",
			current, 0
		}
	);
	return (output);
}

char	*create_prompt(t_minishell *shell)
{
	char	*prompt;
	char	*temp[2];

	if (!shell->interactive_mode)
		return (ft_strdup(""));
	prompt = ft_strdup("\033[38;2;216;185;255mminishell\033[0m");
	if (!has_git() || (has_git() && is_git_dir()))
	{
		temp[0] = str_vec_join((char *[3]){prompt, " > ", 0});
		free(prompt);
		return (temp[0]);
	}
	temp[0] = run_git_command((char *[7]){"git", "-C", ".", "rev-parse", 
		"--abbrev-ref", "HEAD", 0});
	temp[0][ft_strlen(temp[0]) - 1] = '\0';
	temp[1] = str_vec_join((char *[5]){
		prompt, " (\033[38;2;0;255;0m", temp[0],"\033[0m) > ", 0});
	free(prompt);
	free(temp[0]);
	prompt = prepend_statuscode(shell, temp[1]);
	free(temp[1]);
	return (prompt);
}

