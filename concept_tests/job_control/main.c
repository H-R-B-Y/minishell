/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:14:43 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/26 14:10:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#ifndef __USE_POSIX
# define __USE_POSIX
#endif

#ifndef __USE_POSIX199506
# define __USE_POSIX199506
#endif

#include <features.h>
#include <signal.h>
#include <bits/sigaction.h>

extern char **environ;


struct	chld_info
{
	pid_t	pid;
	int		ret;
	int		stat;
	int		sign;
};

struct chld_info long_running_child()
{
	int pid;
	int ret;
	int stat;
	struct chld_info a = {0};
	
	a.pid = fork();
	if (a.pid == 0)
	{
		execve("/usr/bin/cat", (char *[2]){"/usr/bin/cat", 0}, environ);
	}
	else if (a.pid < 0)
		return (perror("fork failed"), a);
	return (a);
}

void	waitonjob(pid_t pgid, struct chld_info **p, int count)
{
	int	ret;
	int	id;
	int	i[2] = {0};

	while (i[0] < count)
	{
		printf("waiting for child\n");
		fflush(stdout);
		id = waitpid(-pgid, &ret, WUNTRACED);
		printf("child returned %d\n", id);
		fflush(stdout);
		i[1] = 0;
		while (i[1] < count)
		{
			if (p[i[1]]->pid != id && ++i[1])
				continue ;
			if (WIFEXITED(ret) || WIFSIGNALED(ret))
			{
				p[i[1]]->ret = ret;
				p[i[1]]->stat = -1;
				if ( WIFSIGNALED(ret))
					p[i[1]]->sign = WTERMSIG(ret);
			}
			i[0]++;
			i[1]++;
		}
	}
	return ;
}

int main ()
{
	struct chld_info	a = {0};
	struct chld_info	b = {0};
	int					sleeping = 0;
	int					ret;
	int					id;
	char				*next;

	a = long_running_child();
	setpgid(a.pid, a.pid);
	b = long_running_child();
	setpgid(b.pid, a.pid);
	tcsetpgrp(STDIN_FILENO, a.pid);
	// signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
WAITJOB:
	waitonjob(a.pid, (struct chld_info *[2]){&a, &b}, 2);
	tcsetpgrp(STDIN_FILENO, getpid());
	if (a.stat == b.stat && a.stat == -1)
		return (printf("children dead\nsignal a: %d\nsignal b: %d", a.sign, b.sign), 0);
	else
	{
		printf("CHILDREN SLEEPING\n");
NEXTLINE:
		next = readline("continue or kill [c/k]: ");
		if (!next)
			return (kill(-a.pid, SIGKILL), -1);
		if (*next == 'c')
		{
			tcsetpgrp(STDIN_FILENO, a.pid);
			kill(-a.pid, SIGCONT);
			waitpid(a.pid, 0, WNOHANG);
			waitpid(b.pid, 0, WNOHANG);
			goto WAITJOB;
		}
		else if (*next == 'k')
		{
			kill(-a.pid, SIGKILL);
			waitpid(a.pid, 0, WNOHANG);
			waitpid(b.pid, 0, WNOHANG);
			return (0);
		}
		else
			goto NEXTLINE;
	}
	return (0);
}
