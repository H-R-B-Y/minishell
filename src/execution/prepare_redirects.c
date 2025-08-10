/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:15:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/09 21:56:55 by cquinter         ###   ########.fr       */
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

static int	_file_to_fds(t_minishell *shell, t_redirect_desc *redr)
{
	if (redr->file_map.to_fd >= shell->ulimit_n)
		return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n", redr->file_map.to_fd), -1);
	if (redr->file_map.name == 0x0)
		return (ft_fprintf(2, "minishell: : No such file or directory\n"), -1); // handle this in caller
	redr->file_map.from_fd = open(redr->file_map.name, t_oflag(redr->type));
	if (redr->file_map.from_fd < 0)
	{
		redr->file_map.from_fd = open(redr->file_map.name,
			t_oflag(redr->type) | O_CREAT, 0755);
	}
	if (redr->file_map.from_fd < 0)
		return (perror("minishell"), -1); // failed to open file
	return (1);
}

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
			// We wont know if a file desc points to anything until we go to map it
			// so we can only check if any of these are greater than the ulimit
			if (redr->fd_map.from_fd >= shell->ulimit_n)
				return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n", redr->fd_map.from_fd), -1);
			if (redr->fd_map.to_fd >= shell->ulimit_n)
				return (ft_fprintf(2, "minishell: %d: Bad file descriptor\n", redr->fd_map.to_fd), -1);
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

static int	_map(t_redirect_desc *desc)
{
	int				current_fd;

	if (!desc)
		return (0);
	if (desc->subtype == CLOSE_FD)
		close(desc->fd_map.to_fd);
	else if (desc->subtype == REDIR_FD)
	{
		current_fd = dup(desc->fd_map.from_fd);
		if (current_fd < 0)
		{
			perror("minishell:filedesc mapping");
			return (-1);
		}
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
	return (0);
}

int	map_fds(t_astnode *node)
{
	t_list			*list;
	t_list			*rd_restore_info;
	
	rd_restore_info = ft_lstnew(NULL);
	list = node->redirect;
	while (list)
	{
		if (prep_rd_restore(list->content, &rd_restore_info) == -1 ||
			_map(list->content) < 0)
			return (rd_list_restore(rd_restore_info), -1);
		list = list->next;
	}
	node->rd_rstr_info = rd_restore_info;
	return (1);
}
