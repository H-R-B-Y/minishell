/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:56:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/07/27 18:43:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

/*
token is:
enum (4)
string (??)
int (4)
int (4)
int (4)
int (4)

*/
int	write_token(struct s_dbg_info *info, t_token *token)
{
	int	byte_count;
	int	int_data;

	int_data = DBG_DT_TOKEN;
	write(info->fd, &int_data, sizeof(int));
	byte_count = (sizeof(int) * 5)
		+ ((ft_strlen(token->raw) + 1)
			* sizeof(char))
		+ sizeof(void *);
	write(info->fd, &byte_count, sizeof(int));
	write(info->fd, &token, sizeof(void *));
	write(info->fd, &token->type, sizeof(int));
	write(info->fd, token->raw, ft_strlen(token->raw) + 1);
	write(info->fd, &token->heredoc_delim, sizeof(int));
	write(info->fd, &token->redirect_file, sizeof(int));
	write(info->fd, &token->quotes_removed, sizeof(int));
	write(info->fd, &token->variables_expanded, sizeof(int));
	return (byte_count + (sizeof(int) * 2));
}

size_t	dbg_write_tokens(struct s_dbg_info *info)
{
	size_t	byte_count;
	t_list	*node;

	if (!(info->fd_available && info->fd_writable))
		return (0);
	node = info->tokens;
	byte_count = 0;
	while (node)
	{
		byte_count += write_token(info, node->content);
		node = node->next;
	}
	ft_lstclear(&info->tokens, 0);
	info->tokens = 0;
	return (byte_count);
}
