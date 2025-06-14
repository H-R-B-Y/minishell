/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:34:45 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/14 16:59:56 by hbreeze          ###   ########.fr       */
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

size_t	write_redirects(struct s_dbg_info *info, t_list *redirects)
{
	int				int_data;
	t_list			*node;
	t_redirect_desc	*cont;
	ssize_t			byte_count;

	byte_count = 0;
	int_data = ft_lstsize(redirects);
	byte_count += write(info->fd, &int_data, sizeof(int));
	node = redirects;
	int_data = DBG_DT_REDR;
	while (node)
	{
		byte_count += write(info->fd, &int_data, sizeof(int));
		cont = node->content;
		byte_count += write(info->fd, &cont->type, sizeof(int));
		byte_count += write(info->fd, &cont->subtype, sizeof(int));
		if (cont->subtype == REDIR_FILE)
		{
			byte_count += write(info->fd, cont->file_map.filename, ft_strlen(cont->file_map.filename) + 1);
			byte_count += write(info->fd, &cont->file_map.to_fd, sizeof(int));
		}
		else
		{
			byte_count += write(info->fd, &cont->fd_map.from_fd, sizeof(int));
			byte_count += write(info->fd, &cont->fd_map.to_fd, sizeof(int));
		}
		node = node->next;
	}
	printf("Wrote %d redirects\n", int_data);
	return (byte_count);
}

size_t	write_cmdv(struct s_dbg_info *info, t_astnode *node)
{
	ssize_t	bytes_count;
	int		int_data;

	bytes_count = 0;
	int_data = ft_arrlen((void *)node->cmdv);
	bytes_count += write(info->fd, &int_data, sizeof(int));
	if (!int_data)
		return (bytes_count);
	int_data = 0;
	while (node->cmdv[int_data])
	{
		bytes_count += write(info->fd, node->cmdv[int_data], ft_strlen(node->cmdv[int_data]));
		int_data++;
	}
	return (bytes_count);
}

size_t	write_node(struct s_dbg_info *info, t_astnode *node)
{
	size_t		byte_count;
	int			int_data;
	void		*null_data;

	int_data = DBG_DT_NODES;
	byte_count = 0;
	byte_count += write(info->fd, &int_data, sizeof(int)); // data type 
	byte_count += write(info->fd, &byte_count, sizeof(int)); // bytes in package (not including this and last int)
	byte_count += write(info->fd, &node, sizeof(void *)); // node ID
	byte_count += write(info->fd, &node->type, sizeof(int));
	byte_count += write(info->fd, &node->left_node, sizeof(void *));
	byte_count += write(info->fd, &node->right_node, sizeof(void *));
	int_data = (int)ft_arrlen((void *)node->tokens);
	byte_count += write(info->fd, &int_data, sizeof(int));
	byte_count += write(info->fd, node->tokens, sizeof(void *) * int_data);
	while(int_data)
		printf("wrote ptr %p\n", &node->tokens[int_data--]);
	null_data = 0;
	byte_count += write(info->fd, &null_data, sizeof(void *));
	byte_count += write(info->fd, &node->return_code, sizeof(int));
	byte_count += write_cmdv(info, node);
	byte_count += write_redirects(info, node->redirect);
	printf("wrote %ld bytes for ast node %p\n", byte_count, node);
	return (byte_count);
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
