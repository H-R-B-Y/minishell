/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:15:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/04 15:06:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// this should be a util function somewhere else!!!!!!!!!!!

int	t_oflag(const int redr_type)
{
	int	flag;

	flag = 0;
	if (redr_type == REDIRECT_IN)
		flag |= O_RDONLY;
	else if (redr_type == REDIRECT_OUT || redr_type == REDIRECT_OUT_A)
		flag |= O_WRONLY;
	if (redr_type == REDIRECT_OUT_A)
		flag |= O_APPEND;
	else if (redr_type != REDIRECT_IN)
		flag |= O_TRUNC;
	return (flag);
}

static int	_file_to_fds(t_list *redrs)
{
	t_list			*index;
	t_redirect_desc	*redr;

	index = redrs;
	while (index)
	{
		redr = index->content;
		if (redr->subtype == REDIR_FD || redr->subtype == CLOSE_FD)
		{
			index = index->next;
			continue ;
		}
		if (redr->file_map.name == 0x0)
			return (ft_printf("minishell: :No such file or directory\n"), -1); // handle this in caller
		redr->file_map.from_fd = open(redr->file_map.name, t_oflag(redr->type));
		if (redr->file_map.from_fd < 0)
		{
			redr->file_map.from_fd = open(redr->file_map.name,
				t_oflag(redr->type) | O_CREAT, 0755);
		}
		if (redr->file_map.from_fd < 0)
			return (perror("minishell"), -1); // failed to open file
		index = index->next;
	}
	return (1);
}

int	prepare_fds(t_astnode *node)
{
	if (!node->redirect)
		return (0);
	if (_file_to_fds(node->redirect) < 0)
		return (-1);
	return (1);
}

static void	_map(t_redirect_desc *desc)
{
	int				current_fd;

	if (!desc)
		return ;
	if (desc->subtype == CLOSE_FD)
		close(desc->fd_map.to_fd);
	else if (desc->subtype == REDIR_FD)
	{
		current_fd = dup(desc->fd_map.from_fd);
		dup2(current_fd, desc->fd_map.to_fd);
		close(current_fd);
	}
	else if (desc->file_map.to_fd >= 0)
	{
		dup2(desc->file_map.from_fd, desc->file_map.to_fd);
		close(desc->file_map.from_fd);
	}
	else
	{
		dup2(desc->file_map.from_fd, STDERR_FILENO);
		dup2(desc->file_map.from_fd, STDOUT_FILENO);
		close(desc->file_map.from_fd);
	}
}

void	map_fds(t_astnode *node)
{
	t_list			*list;

	list = node->redirect;
	while (list)
	{
		_map(list->content);
		list = list->next;
	}
}
