/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:11:09 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:41:00 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	_close_rstore_fds(t_restore_rds *info)
{
	if (info->dupped1 >= 0)
		close(info->dupped1);
	if (info->dupped2 >= 0)
		close(info->dupped2);
}

int	init_rd_rstr_info(t_restore_rds **info, t_redirect_desc *desc)
{
	*info = ft_calloc(1, sizeof(t_restore_rds));
	if (!*info)
		return (-1);
	ft_memset(*info, -1, sizeof(t_restore_rds));
	if (!desc->subtype && desc->file_map.to_fd < 0)
		(*info)->subtype = 12;
	else
		(*info)->subtype = desc->subtype;
	return (0);
}
