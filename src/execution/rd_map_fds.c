/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_map_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:15:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/24 16:51:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	prep_rd_restore(t_redirect_desc *desc, t_list **rd_restore)
{
	t_list			*new_rd;
	t_restore_rds	*info;

	if (!desc)
		return (1);
	if (init_rd_rstr_info(&info, desc) == -1)
		return (-1);
	if (desc->subtype == REDIR_FD || desc->subtype == CLOSE_FD)
		info->to_fd = desc->fd_map.to_fd;
	else if (desc->file_map.to_fd >= 0)
		info->to_fd = desc->file_map.to_fd;
	else
	{
		info->dupped2 = dup(STDERR_FILENO);
		if (info->dupped2 == -1)
			return (free(info), -1);
		info->to_fd = STDOUT_FILENO;
	}
	info->dupped1 = dup(info->to_fd);
	if (info->dupped1 == -1 && errno != EBADF)
		return (_close_rstore_fds(info), free(info), -1);
	new_rd = ft_lstnew(info);
	if (!new_rd)
		return (_close_rstore_fds(info), free(info), -1);
	return (ft_lstadd_front(rd_restore, new_rd), 0);
}

static int	_map(t_redirect_desc *desc)
{
	if (!desc)
		return (0);
	if (desc->subtype == CLOSE_FD)
		close(desc->fd_map.to_fd);
	else if (desc->subtype == REDIR_FD)
	{
		desc->current_fd = dup(desc->fd_map.from_fd);
		if (desc->current_fd < 0)
			return (perror("minishell: filedesc mapping"), -1);
		dup2(desc->current_fd, desc->fd_map.to_fd);
		close(desc->current_fd);
	}
	else if (desc->file_map.to_fd >= 0
		&& desc->file_map.from_fd != desc->file_map.to_fd)
	{
		dup2(desc->file_map.from_fd, desc->file_map.to_fd);
		close(desc->file_map.from_fd);
	}
	else if (desc->file_map.to_fd == -1)
	{
		dup2(desc->file_map.from_fd, STDERR_FILENO);
		dup2(desc->file_map.from_fd, STDOUT_FILENO);
		close(desc->file_map.from_fd);
	}
	return (0);
}

int	map_fds(t_astnode *node)
{
	t_list	*list;
	t_list	*rd_restore_info;

	rd_restore_info = ft_lstnew(NULL);
	list = node->redirect;
	while (list)
	{
		if (prep_rd_restore(list->content, &rd_restore_info) == -1
			|| _map(list->content) < 0)
			return (ft_lstclear(&rd_restore_info, free),
				perror("something went wrong here"),
				rd_list_restore(rd_restore_info), -1);
		list = list->next;
	}
	node->rd_rstr_info = rd_restore_info;
	return (1);
}
