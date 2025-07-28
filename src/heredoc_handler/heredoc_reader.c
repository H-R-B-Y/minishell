/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:43:46 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 16:45:36 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;

char	*s_get_envany(t_minishell *shell, const char *name);

static size_t	_replace_var(struct s_ast_internal *meta,
	const int temp_file,
	const char *line
)
{
	size_t	i;
	char	*strs[2];

	i = 0;
	if (line[i + 1] && ft_iswhitespace(line[i + 1]))
		return (write(temp_file, "$", 1), 1);
	i++;
	while (line[i] && !ft_iswhitespace(line[i]))
		i++;
	strs[0] = ft_substr(line, 0, i); // plus one?
	strs[1] = get_var(meta->shell, strs[0] + 1);
	write(temp_file, strs[1], ft_strlen(strs[1]));
	return (free(strs[1]), free(strs[0]), i);
}

static int	write_str(struct s_ast_internal *meta,
	const char *line,
	int temp_file,
	short flags
)
{
	size_t	i;

	i = 0;
	while ((flags & 2) && line[i] && line[i] == '\t')
		++i;
	while (line[i])
	{
		if (line[i] == '$' && (flags & 1))
			i += _replace_var(meta, temp_file, line + i);
		else
			write(temp_file, &line[i++], 1);
	}
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
	if (status == READ_FATAL)
		perror_exit(meta->shell, "minishell:heredoc");
	return (0 - (!(status == READ_OK || status == READ_EOF)));
}
