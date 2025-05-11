/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_newline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:05:16 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/06 20:23:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <term.h>

# include "./libft.h"

/*
This test is here bacause in bash, when a command is written
with either:
- unfinished quotes / parenthesis
- heredoc

the readline prompt continues to allow input until either the
unfinished quotes / parenthesis are closed or the HEREDOC
deliminator is hit.

however, when you press up again in bash, the whole previous
command including the newline characters is put into the buffer.

I just wanted to check that if that kind of history is passed
to our prompt, we are able to split the lines and ensure that the
lines that come after are treated in the same way as the original
command treated them.

*/

int main()
{
	char	*str;
	char	**line;
	int		i;

	add_history("Hello\nworld\nthis\nis\nHarvey.\n");
	str = readline("press the up arrow -> ");
	if (!str || !*str)
		return (0);
	line = ft_split(str, '\n');
	i = 0;
	printf("\n");
	while (line[i])
		printf("line number %d : %s\n", i, line[i++]);
	free(str);
	ft_arrclear((void *)line, free);
	rl_clear_history();
	return (0);
}