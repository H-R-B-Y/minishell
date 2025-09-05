/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:47:07 by hbreeze           #+#    #+#             */
/*   Updated: 2025/08/24 18:39:52 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

size_t	dbg_write_end(const struct s_dbg_info *info)
{
	int	dt;

	if (!(info->fd_writable && info->fd_available))
		return (0);
	dt = DBG_DT_DONE;
	(void)!write(info->fd, &dt, sizeof(int));
	return (sizeof(int));
}
