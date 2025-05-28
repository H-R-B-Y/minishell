/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:04:31 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 16:56:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

int	write_states(struct s_dbg_info *info)
{
	t_list	*node;
	size_t	state_count;
	int		byte_count;
	int		dt;

	if (!(info->fd_writable && info->fd_available))
		return (0);
	dt = DBG_DT_STATE;
	write(info->fd, &dt, sizeof(int));
	state_count = ft_lstsize(info->states);
	byte_count = state_count * sizeof(int);
	write(info->fd, &byte_count, sizeof(int));
	node = info->states;
	while (node)
	{
		dt = (int)(unsigned long int)node->content;
		write(info->fd, &dt, sizeof(int));
		node = node->next;
	}
	return ((state_count + 2) * sizeof(int));
}
