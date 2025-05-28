/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:57:22 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/28 15:05:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/v_dbg.h"

int	add_state(struct s_dbg_info *info, int state)
{
	if (!(info->fd_writable && info->fd_available))
		return ;
	ft_lstadd_back(&info->states, ft_lstnew((void *)(unsigned long int)state));
}

int	add_token(struct s_dbg_info *info, t_token *token)
{
	if (!(info->fd_writable && info->fd_available))
		return ;
	ft_lstadd_back(&info->states, ft_lstnew(token));
}

int	add_nodes(struct s_dbg_info *info, t_astnode *node)
{
	if (!(info->fd_writable && info->fd_available))
		return ;
	ft_lstadd_back(&info->states, ft_lstnew(node));
}
