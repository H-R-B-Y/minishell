/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:19:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/05 15:43:30 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/get_next_line.h"

extern char	**environ;

int	has_git(void)
{
	static int	called = -1;
	if (called < 0)
	{
		called = 1;
		if (access("/usr/bin/git", F_OK))
			called = 0;
	}
	return (called);
}

char	*get_return(int data[2], const int ret)
{
	char	*buff[2];
	int		stat;

	if (WIFEXITED(ret))
	{
		stat = WEXITSTATUS(ret);
		if (stat)
			return (close(data[0]), (char *)0);
	}
	else if (WIFSIGNALED(ret) || WIFSTOPPED(ret))
		return (close(data[0]), (char *)0);
	buff[0] = get_next_line(data[0]);
	while (1)
	{
		buff[1] = get_next_line(data[0]);
		if (!buff[1])
			break ;
		ft_dirtyswap((void *)&buff[0],
			str_vec_join((const char *[3]){buff[0], buff[1], 0}), free);
		free(buff[1]);
	}
	return (close(data[0]), buff[0]);
}

char	*run_git_command(const char **argv)
{
	int		p[2];
	pid_t	chld;
	int		ret;

	if (!has_git())
		return (0);
	if (pipe(p) == -1)
		return (0);
	chld = fork();
	if (chld == -1)
		return (close(p[0]), close(p[1]), (char *)0);
	if (chld == 0)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		close(STDERR_FILENO);
		execve("/usr/bin/git", (void *)argv, environ);
		exit(1);
	}
	close(p[1]);
	waitpid(chld, &ret, 0);
	return (get_return(p, ret));
}

int	is_git_dir(void)
{
	static const char	*argv[6] = {
		"git", "-C", ".", "rev-parse", "--is-inside-work-tree", 0
	};
	char				*out;
	int					code;

	code = 0;
	out = run_git_command((void *)argv);
	if (!out)
		return (code);
	if (ft_strrchr(out, '\n'))
		*(ft_strrchr(out, '\n')) = '\0';
	if (!ft_strcmp(out, "true"))
		code = 1;
	free(out);
	return (code);
}

int	is_git_dirty(void)
{
	static const char	*argv[4] = {
		"git", "status", "--porcelain=v1", 0
	};
	char				*out;
	int					code;

	code = 0;
	out = run_git_command(argv);
	if (!out)
		return (free(out), code);
	if (ft_strrchr(out, '\n'))
		*(ft_strrchr(out, '\n')) = '\0';
	if (ft_strlen(out) > 0)
		code = 1;
	free(out);
	return (code);
}
