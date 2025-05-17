/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:19:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/17 17:58:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ;

int	has_git(void)
{
	if (access("/usr/bin/git", F_OK))
		return (0);
	return (1);
}

char *run_git_command(char **argv)
{
	int		p[2];
	pid_t	chld;
	char	*buff[2];
	
	if (!has_git())
		return (0);
	if (pipe(p) == -1)
		return (0);
	chld = fork();
	if (chld == -1)
		return (0);
	if (chld == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execve("/usr/bin/git", argv, environ);
		exit(1);
	}
	close(p[1]);
	buff[0] = get_next_line(p[0]);
	while (1)
	{
		buff[1] = get_next_line(p[0]);
		if (!buff[1])
			break ;
		buff[0] = str_vec_join((char *[2]){buff[0], buff[1]});
		free(buff[1]);
	}
	close(p[0]);
	return (buff[0]);
}


int	is_git_dir(void)
{
	static const char *argv[5] = {
		"git", "-C", ".", "rev-parse", "--is-inside-work-tree"
	};
	char	*out;
	int		code;

	out = run_git_command((void *)argv);
	if (!ft_strncmp(out, "true", ft_strlen(out)))
		code = 1;
	code = 0;
	free(out);
	return (code);
}
