/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_items.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:57:22 by hbreeze           #+#    #+#             */
/*   Updated: 2025/09/25 12:43:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/v_dbg.h"

size_t	dbg_add_state(struct s_dbg_info *info, int state)
{
	if ((info && !(info->fd_writable && info->fd_available)) || !info)
		return (0);
	ft_lstadd_back(&info->states, ft_lstnew((void *)(unsigned long int)state));
	return (1);
}

size_t	dbg_add_token(struct s_dbg_info *info, t_token *token)
{
	if (!(info->fd_writable && info->fd_available))
		return (0);
	ft_lstadd_back(&info->tokens, ft_lstnew(token));
	return (1);
}

size_t	dbg_add_nodes(struct s_dbg_info *info, t_astnode *node)
{
	if (!(info->fd_writable && info->fd_available))
		return (0);
	ft_lstadd_back(&info->nodes, ft_lstnew(node));
	return (1);
}
