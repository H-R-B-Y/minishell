/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_prep_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:14:36 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 00:29:53 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	_file_to_fds(t_minishell *shell, t_redirect_desc *redr)
{
	if (redr->file_map.to_fd >= shell->ulimit_n)
		return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n",
				redr->file_map.to_fd), -1);
	if (redr->file_map.name == 0x0)
		return (ft_fprintf(2, "minishell: : No such file or directory\n"), -1);
	redr->file_map.from_fd = open(redr->file_map.name, t_oflag(redr->type));
	if (redr->file_map.from_fd < 0)
	{
		redr->file_map.from_fd = open(redr->file_map.name,
				t_oflag(redr->type) | O_CREAT, 0644);
	}
	if (redr->file_map.from_fd < 0)
		return (perror("minishell"), -1);
	return (1);
}

/* Note:
// We wont know if a file desc points to anything until we go to map it
// so we can only check if any of these are greater than the ulimit
*/
static int	_validate_file_to_fds(t_minishell *shell, t_list *redrs)
{
	t_list			*index;
	t_redirect_desc	*redr;

	index = redrs;
	while (index)
	{
		redr = index->content;
		if (redr->subtype == REDIR_FD || redr->subtype == CLOSE_FD)
		{
			if (redr->fd_map.from_fd >= shell->ulimit_n)
				return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n",
						redr->fd_map.from_fd), -1);
			if (redr->fd_map.to_fd >= shell->ulimit_n)
				return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n",
						redr->fd_map.to_fd), -1);
			index = index->next;
			continue ;
		}
		else if (_file_to_fds(shell, redr) < 0)
			return (-1);
		index = index->next;
	}
	return (1);
}

int	prepare_fds(t_minishell *shell, t_astnode *node)
{
	if (!node->redirect)
		return (0);
	if (_validate_file_to_fds(shell, node->redirect) < 0)
	{
		node->return_code = 1;
		return (-1);
	}
	return (1);
}
