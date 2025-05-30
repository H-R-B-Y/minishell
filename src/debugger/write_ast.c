/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:34:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/05/30 19:29:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/v_dbg.h"
#include "../../include/minishell.h"

/*
AST node is:
type		- enum		- sizeof(int)
left node	- ptr		- sizeof(void *)
right node	- ptr		- sizeof(void *)
tokens		- ptr[]		- sizeof(void *) * ft_arrlen(tokens)
return code	- int		- sizeof(int)

we also need to write:
size of package		- int	- sizeof(int)
size of token arr	- int	- sizeof(int)
*/

int	write_node(struct s_dbg_info *info, t_astnode *node)
{
	int		byte_count;
	int		int_data;
	void	*null_data;

	byte_count = (sizeof(int) * 3) // type, return code, arr len
		+ (sizeof(void *) * 3) // left node, right node, ME 
		+ (sizeof(void *)
			* (ft_arrlen((void *)node->tokens) + 1));
	int_data = DBG_DT_NODES;
	write(info->fd, &int_data, sizeof(int)); // data type 
	write(info->fd, &byte_count, sizeof(int)); // bytes in package (not including this and last int)
	write(info->fd, &node, sizeof(void *)); // node ID
	write(info->fd, &node->type, sizeof(int));
	write(info->fd, &node->left_node, sizeof(void *));
	write(info->fd, &node->right_node, sizeof(void *));
	int_data = (int)ft_arrlen((void *)node->tokens);
	write(info->fd, &int_data, sizeof(int));
	write(info->fd, node->tokens, sizeof(void *) * int_data);
	while(int_data)
		printf("wrote ptr %p\n", &node->tokens[int_data--]);
	null_data = 0;
	write(info->fd, &null_data, sizeof(void *));
	write(info->fd, &node->return_code, sizeof(int));
	printf("wrote %d bytes for ast node %p\n", byte_count, node);
	return (byte_count + (sizeof(int) * 2));
}

size_t	dbg_write_nodes(struct s_dbg_info *info)
{
	t_list	*node;
	size_t	byte_count;

	if (!(info->fd_available && info->fd_writable))
		return (0);
	node = info->nodes;
	byte_count = 0;
	while (node)
	{
		byte_count += write_node(info, node->content);
		node = node->next;
	}
	ft_lstclear(&info->nodes, 0);
	info->nodes = 0;
	return (byte_count);
}
