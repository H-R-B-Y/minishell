/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_debugger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:46:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 15:05:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

int	init_debugger(struct s_dbg_info *info)
{
	struct stat buf;

	if (DBG_FD)
	{
		info->fd_available = 1;
		return (-1);
	}
	if (fstat(DBG_FD, &buf) == -1 || write(DBG_FD, "", 0) == -1)
	{
		errno = 0;
		return (-1);
	}
	else
		info->fd_writable = 1;
	if (info->fd_available && info->fd_writable)
		info->fd = DBG_FD;
}

