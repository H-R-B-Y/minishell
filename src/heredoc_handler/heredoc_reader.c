/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:43:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/19 18:27:14 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;

char	*s_get_envany(t_minishell *shell, const char *name);

static int	write_str(struct s_ast_internal *meta,
	const char *line,
	int temp_file,
	short flags
)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while ((flags & 2) && line[i] && line[i] == '\t')
		++i;
	if (ft_strchr(line, '$') && (flags & 1))
	{
		tmp = expand_and_split(meta->shell, &line[i], 0);
		write(temp_file, tmp[0], ft_strlen(tmp[0]));
		ft_arrclear((void *)tmp, free);
	}
	else
		write(temp_file, &line[i], ft_strlen(&line[i]));
	if (last_newline_not_end(line))
		write(temp_file, "\n", 1);
	return (1);
}

int	_read_heredoc(struct s_ast_internal *meta,
	const char *delim,
	const int temp_file,
	const short flags
)
{
	char				*temp;
	t_readline_retcode	status;

	meta->rldata->hdoc = 1;
	status = next_line(meta->rldata, "heredoc > ");
	while (status == READ_OK || status == READ_NOTHING)
	{
		if (g_global_signal != 0)
			return (-1);
		temp = meta->rldata->last_line;
		if (!ft_strcmp(delim, temp))
			break ;
		if (status == READ_OK)
			write_str(meta, temp, temp_file, flags);
		status = next_line(meta->rldata, "heredoc > ");
	}
	meta->rldata->hdoc = 0;
	if (status == READ_FATAL)
		perror_exit(meta->shell, "heredoc");
	return (0 - (!(status == READ_OK || status == READ_EOF)));
}
