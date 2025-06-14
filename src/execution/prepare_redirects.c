/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:15:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/14 16:03:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// this should be a util function somewhere else!!!!!!!!!!!

int	redrtype_to_oflag(const int redr_type)
{
	int	flag;

	flag = 0;
	if (redr_type == REDIRECT_INPUT)
		flag |= O_RDONLY;
	else if (redr_type == REDIRECT_OUTPUT || redr_type == REDIRECT_OUTPUT_APPEND)
		flag |= O_WRONLY;
	if (redr_type == REDIRECT_OUTPUT_APPEND)
		flag |= O_APPEND;
	return (flag);
}

t_redirect_desc	*file_to_fd_mapper(const t_redirect_desc *redr)
{
	t_redirect_desc	*p;

	p = ft_calloc(sizeof(t_redirect_desc), 1);
	if (!p)
		return (0);
	if (redr->subtype == REDIR_FD)
	{
		*p = *redr;
		return (p);
	}
	p->type = redr->type;
	p->subtype = REDIR_FD;
	p->fd_map.to_fd = redr->file_map.to_fd;
	p->fd_map.from_fd = open(redr->file_map.filename, redrtype_to_oflag(redr->type));
	if (p->fd_map.from_fd == -1)
	{
		if (errno == ENOENT)
			p->fd_map.from_fd = open(redr->file_map.filename, redrtype_to_oflag(redr->type) | O_CREAT, 0755);
		if (errno && errno != ENOENT)
			return (0); // free p;
	}
	return (p);
}

int	prepare_fds(t_astnode *node)
{
	t_list	*corrected;

	if (!node->redirect)
		return (0);
	corrected = ft_lstmap(node->redirect, (void *)file_to_fd_mapper, free); // WARN: free is not good enough, redirects will leak
	if (!corrected)
		return (perror("minishell"), -1);
	ft_lstclear(&node->redirect, destroy_redirect);
	node->redirect = corrected;
	return (1);
}
