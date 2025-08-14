/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_list_restore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:07:15 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:40:39 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_fd_restore(t_restore_rds *info)
{
	if (!info)
		return (0);
	if (info->subtype == 12)
	{
		if ((info->dupped2 >= 0 && dup2(info->dupped2, STDERR_FILENO) == -1)
			|| ((info->dupped2 < 0 && close(STDERR_FILENO) == -1)))
			return (ft_fprintf(2, "minishell: %d: ", STDERR_FILENO));
	}
	if ((info->dupped1 >= 0 && dup2(info->dupped1, info->to_fd) == -1)
		|| ((info->dupped1 < 0 && close(info->to_fd) == -1)))
		return (ft_fprintf(2, "minishell: %d: ", info->to_fd));
	_close_rstore_fds(info);
	return (0);
}

void	rd_list_restore(t_list *info_lst)
{
	t_list			*list;

	list = info_lst;
	while (list)
	{
		if (rd_fd_restore(list->content))
			perror(NULL);
		list = list->next;
	}
}
