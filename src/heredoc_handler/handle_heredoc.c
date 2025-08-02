/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:22:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/28 16:25:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_global_signal;

int		_read_heredoc(struct s_ast_internal *meta, const char *delim,
	const int temp_file, const short flags);

static int	prep_heredoc(struct s_ast_internal *meta,
	const char *delim,
	short handle_vars
)
{
	char	*strs[3];
	int		temp_file[2];

	strs[0] = rem_quotes(delim);
	if (strs[0][0] == '-')
		handle_vars += 2;
	strs[1] = ft_itoa(get_my_pid());
	ft_dirtyswap((void *)&strs[1],
		(void *)ft_strjoin("/tmp/minishell_heredoc_", strs[1]), free);
	temp_file[0] = open(strs[1],
			O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (temp_file[0] == -1)
		return (free(strs[0]), free(strs[1]), -1);
	if (_read_heredoc(meta, strs[0] + !!(handle_vars & 2),
			temp_file[0], handle_vars) != 0)
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
	const char *delim
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
	temp_file[0] = prep_heredoc(meta, delim, handle_vars);
	(*output) = (t_redirect_desc){.type = REDIRECT_HD, .subtype = REDIR_FD,
		.fd_map.from_fd = temp_file[0], .fd_map.to_fd = STDIN_FILENO};
	if (temp_file[0] < 0)
		return (free(output), NULL);
	return (output);
}
