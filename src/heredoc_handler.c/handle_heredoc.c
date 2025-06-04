/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:22:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/04 17:07:45 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*s_get_envany(t_minishell *shell, char *name);

void	_replace_var(t_minishell *shell, int temp_file, char *line)
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
		var[1] = s_get_envany(shell, var[0]);
		free(var[0]);
		write(temp_file, var[1], ft_strlen(var[1]));
		i[0] = i[1];
	}
}

int	_read_heredoc(t_minishell *shell, char *delim, int temp_file, short handlevar)
{
	char	*temp;
	int		status;

	status = next_line(&shell->rldata, "heredoc");
	while(status == READ_OK)
	{
		temp = shell->rldata.last_line;
		if (ft_strcmp(delim, temp))
			break ;
		if (handlevar && ft_strchr(temp, '$'))
			_replace_var(shell, temp_file, temp);
		else
			write(temp_file, temp, ft_strlen(temp));
		status = next_line(&shell->rldata, "heredoc");
	}
	if (status != READ_OK)
		return (-1);
	return (0);
}

t_redirect_desc	*handle_heredoc(t_minishell *shell, char *delim)
{
	t_redirect_desc	*output;
	char			*clean_heredoc;
	short			handle_vars;
	int				temp_file;

	if (!delim || !shell)
		return (0);
	output = calloc(1, sizeof(t_redirect_desc));
	if (!output)
		return (0);
	handle_vars = 0;
	if (!ft_strchr(delim, '"') && !ft_strchr(delim, '\''))
		handle_vars = 1;
	clean_heredoc = remove_quotes(delim, shell);
	temp_file = open(getcwd(0, 0), O_RDONLY | __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (temp_file == -1)
	{
		perror("minishell: heredoc");
		free(output);
		return (0);
	}
	_read_heredoc(shell, clean_heredoc, temp_file, handle_vars);
	(*output) = (t_redirect_desc){.from_fd = temp_file, .to_fd = 0, .type = REDIRECT_HEREDOC};
	return (output);
}
