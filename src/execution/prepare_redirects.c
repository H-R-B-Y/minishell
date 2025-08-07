/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:15:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/07 17:52:45 by cquinter         ###   ########.fr       */
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
			return (ft_fprintf(2, "minishell: :No such file or directory\n"), -1); // handle this in caller
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
	{
		node->return_code = 1;
		return (-1);
	}
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

void	prep_rd_restore(t_redirect_desc *desc)
{
	int	temp_fd[2];
	
	ft_memset(temp_fd, -1, size_t(temp_fd) * 2);
	if (!desc)
		return ;
	if (desc->subtype == REDIR_FD || desc->subtype == CLOSE_FD)
		temp_fd[0] = dup(desc->fd_map.to_fd);
	else if (desc->file_map.to_fd >= 0)
		temp_fd[0] = dup(desc->file_map.to_fd);
	else
	{
		temp_fd[1] = dup(STDERR_FILENO);
		temp_fd[0] = dup(STDOUT_FILENO);
	}
	desc->restore_fd = temp_fd;
}

void	rd_restore(t_redirect_desc *desc)
{
	int	restore_fd[2];
	int	i;
	
	restore_fd = desc->to_restore;
	if (!desc || restore_fd[0] == -1)
		return ;
	if (desc->subtype == REDIR_FD || desc->subtype == CLOSE_FD)
		dup2(restore_fd[0], desc->fd_map.to_fd);
	else if (desc->file_map.to_fd >= 0)
		dup2(restore_fd[0], desc->file_map.to_fd);
	else
	{
		dup2(restore_fd[1], STDERR_FILENO);
		dup2(restore_fd[0], STDOUT_FILENO);
	}
	i = 0;
	while (rd_restore[i] >= 0)
		close(rd_restore[i++]);
}

void	restore_fds(t_astnode *node)
{
	t_list			*list;

	list = node->redirect;
	while (list)
	{
		prep_rd_restore(list->content);
		_map(list->content);
		list = list->next;
	}
}

void	map_fds(t_astnode *node)
{
	t_list			*list;

	list = node->redirect;
	while (list)
	{
		prep_rd_restore(list->content);
		_map(list->content);
		list = list->next;
	}
}
