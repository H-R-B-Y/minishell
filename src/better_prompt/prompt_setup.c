/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:46:41 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/14 19:25:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
HOLY THANKS
stackoverflow.com/
questions/8806643/colorized-output-breaks-linewrapping-with-readline

colour codes were completely ruining the prompt, but they just need to be wrapped
in codes that tell readline not to count their width
*/

char	*make_colour_string(short r, short g, short b)
{
	char	*parts[9];

	parts[0] = "\001\033[38;2;";
	if (r > 0 && r < 256)
		parts[1] = ft_itoa(r);
	else
		parts[1] = ft_strdup("0");
	parts[2] = ";";
	if (g > 0 && g < 256)
		parts[3] = ft_itoa(g);
	else
		parts[3] = ft_strdup("0");
	parts[4] = ";";
	if (b > 0 && b < 256)
		parts[5] = ft_itoa(b);
	else
		parts[6] = ft_strdup("0");
	parts[6] = "m\002";
	parts[7] = 0;
	parts[8] = str_vec_join((const char **)parts);
	free(parts[1]);
	free(parts[3]);
	free(parts[5]);
	return (parts[8]);
}

char	*status_code_part(const t_minishell *shell)
{
	char	*parts[10];

	if (shell->return_code == 0)
		parts[0] = "\001\033[38;2;100;255;100m\002";
	else
		parts[0] = "\001\033[38;2;255;100;100m\002";
	parts[1] = " - ";
	parts[2] = ft_itoa(shell->return_code);
	parts[3] = " - ";
	parts[4] = "\001\033[0m\002";
	parts[5] = 0;
	parts[6] = str_vec_join((const char **)parts);
	free(parts[2]);
	return (parts[6]);
}

// WARN: this will always return an allocated string, NOT NULL
char	*git_branch_part(void)
{
	char	*parts[10];

	if (!has_git() || (has_git() && !is_git_dir()))
		return (ft_strdup(""));
	parts[0] = "(";
	if (is_git_dirty())
		parts[1] = "\001\033[38;2;255;100;100m\002";
	else
		parts[1] = "\001\033[38;2;100;255;100m\002";
	parts[2] = run_git_command((const char *[7])
		{"git", "-C", ".", "rev-parse", "--abbrev-ref", "HEAD", 0});
	if (ft_strchr(parts[2], '\n'))
		*(ft_strchr(parts[2], '\n')) = '\0';
	if (!parts[2])
		parts[2] = ft_strdup("master");
	parts[3] = "\001\033[0m\002";
	parts[4] = ")";
	parts[5] = 0;
	parts[6] = str_vec_join((const char **)parts);
	free(parts[2]);
	return (parts[6]);
}

char	*directory_part(void)
{
	size_t	count;
	char	*dir[2];
	char	*output;

	dir[0] = getcwd(0, 0);
	count = ft_strcountchar(dir[0], '/');
	dir[1] = dir[0];
	while (count > 1)
	{
		dir[1] = ft_strchr(dir[1], '/') + 1;
		count--;
	}
	if (dir[1] != dir[0])
		dir[1] -= 1;
	output = str_vec_join((const char *[]){" ", dir[1], " ", 0});
	free(dir[0]);
	return (output);
}

char	*create_prompt(const t_minishell *shell)
{
	char		*prompt;
	char		*parts[10];

	has_git();
	parts[0] = status_code_part(shell);
	parts[1] = directory_part();
	parts[2] = git_branch_part();
	prompt = str_vec_join((const char *[5]){
			parts[0], parts[1], parts[2], " > ", 0
		});
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	return (prompt);
}
