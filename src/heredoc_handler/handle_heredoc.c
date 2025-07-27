/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:22:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 19:36:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;

char	*s_get_envany(t_minishell *shell, char *name);

static int	_replace_var(struct s_ast_internal *meta, int temp_file, char *line)
{
	size_t	i[2];
	char	*var[2];

	ft_bzero(i, sizeof(size_t) * 2);
	while (line[i[0]])
	{
		if (line[i[0]] != '$')
		{
			write(temp_file, &line[i[0]], 1);
			i[0]++;
		}
		i[1] = i[0] + 1;
		while (line[i[1]] && line[i[1]] != '$' && !ft_iswhitespace(line[i[1]]))
			i[1]++;
		var[0] = ft_substr(line, i[0] + 1, i[1] - i[0]);
		if (!var[0])
			return (-1);
		var[1] = s_get_envany(meta->shell, var[0]);
		free(var[0]);
		write(temp_file, var[1], ft_strlen(var[1]));
		i[0] = i[1];
	}
	return (1);
}

static int	_read_heredoc(struct s_ast_internal *meta,
	const char *delim,
	int temp_file,
	short flags)
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
		while ((flags & 2) && temp[0] == '\t')
			temp++;
		if (status == READ_OK && (flags & 1) && ft_strchr(temp, '$')
			&& _replace_var(meta, temp_file, temp) < 0)
			return (-1);
		write(temp_file, temp, ft_strlen(temp) * (status == READ_OK));
		write(temp_file, "\n", 1);
		status = next_line(meta->rldata, "heredoc > ");
	}
	if (status == READ_FATAL)
		perror_exit(meta->shell, "minishell:heredoc");
	else if (!(status == READ_OK || status == READ_EOF))
		return (-1);
	return (0);
}

static int	prep_heredoc(struct s_ast_internal *meta,
	const char *delim,
	short handle_vars
)
{
	char	*strs[2];
	int		temp_file[2];

	strs[0] = rem_quotes(delim);
	strs[1] = ft_itoa(get_my_pid());
	ft_dirtyswap((void *)&strs[1],
		(void *)ft_strjoin("/tmp/minishell_heredoc_", strs[1]), free);
	temp_file[0] = open(strs[1],
			O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (temp_file[0] == -1)
		return (free(strs[0]), free(strs[1]), -1);
	if (_read_heredoc(meta, strs[0], temp_file[0], handle_vars) != 0)
	{
		if (g_global_signal == SIGINT)
			meta->error = AST_ERR_HEREDOC_EXIT;
		return (free(strs[0]), free(strs[1]), -1);
	}
	close(temp_file[0]);
	temp_file[0] = open(strs[1], O_RDONLY);
	if (temp_file[0] == -1)
		return (free(strs[0]), free(strs[1]), -1);
	return (unlink(strs[1]), free(strs[0]), free(strs[1]), temp_file[0]);
}

// GOOD READ BTW: 
// https://www.oilshell.org/blog/2016/10/18.html
t_redirect_desc	*handle_heredoc(struct s_ast_internal *meta,
	const char *delim,
	t_token *heredoc
)
{
	t_redirect_desc	*output;
	short			handle_vars;
	int				temp_file[2];

	if (!delim || !meta)
		return (0);
	output = ft_calloc(1, sizeof(t_redirect_desc));
	if (!output)
		return (0);
	handle_vars = 0;
	if (!ft_strchr(delim, '"') && !ft_strchr(delim, '\''))
		handle_vars = 1;
	temp_file[0] = prep_heredoc(meta, delim,
			handle_vars + (!!ft_strchr(heredoc->raw, '-') * 2));
	(*output) = (t_redirect_desc){.type = REDIRECT_HD, .subtype = REDIR_FD,
		.fd_map.from_fd = temp_file[0], .fd_map.to_fd = STDIN_FILENO};
	if (temp_file[0] < 0)
		return (free(output), NULL);
	return (output);
}
