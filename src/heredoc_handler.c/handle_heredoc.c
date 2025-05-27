/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:22:39 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/27 15:36:45 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_heredoc_handle_vars(t_minishell *shell, char *delim, int temp_file)
{
	char	*temp;

	
}

int	read_heredoc_no_vars(t_minishell *shell, char *delim, int temp_file)
{
	
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
	clean_heredoc = sanitize_heredoc(delim);
	temp_file = open("/", O_RDONLY | __O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	if (temp_file == -1)
	{
		perror("minishell: heredoc");
		free(output);
		return (0);
	}
	if (handle_vars)
		read_heredoc_handle_vars(shell, clean_heredoc, temp_file);
	else
		read_heredoc_no_vars(shell, clean_heredoc, temp_file);
	(*output) = (t_redirect_desc){.from_fd = temp_file, .to_fd = 0, .type = REDIRECT_HEREDOC};
}
