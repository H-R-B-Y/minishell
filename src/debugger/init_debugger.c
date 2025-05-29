/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_debugger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:46:24 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/29 18:02:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

int	init_debugger(struct s_dbg_info *info)
{
	struct stat buf;

	if (FD_DBG)
	{
		info->fd_available = 1;
		return (-1);
	}
	if (fstat(FD_DBG, &buf) == -1 || write(FD_DBG, "", 0) == -1)
	{
		errno = 0;
		return (-1);
	}
	else
		info->fd_writable = 1;
	if (info->fd_available && info->fd_writable)
		info->fd = FD_DBG;
}

struct s_dbg_info *static_debug_info(void)
{
	static struct s_dbg_info	info = {0};
	return (&info);
}
