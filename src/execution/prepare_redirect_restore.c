#include "../../include/minishell.h"

static void _close_rstore_fds(t_restore_rds *info)
{
	if (info->dupped1 >= 0)
		close(info->dupped1);
	if (info->dupped2 >= 0)
		close(info->dupped2);
}
int	init_rd_rstr_info(t_restore_rds **info, t_redirect_desc *desc)
{
	*info = ft_calloc(1, sizeof(info));
	if (!*info)
		return (-1);
	ft_memset(*info, -1, sizeof(t_restore_rds));
	(*info)->subtype = desc->subtype;
	return (0);
}

int	prep_rd_restore(t_redirect_desc *desc, t_list **rd_restore)
{
	t_list			*new_rd;
	t_restore_rds	*info;
	
	if (!desc)
		return (1);
	if (init_rd_rstr_info(&info, desc) == -1)
		return (-1);
	if (desc->subtype == REDIR_FD || desc->subtype == CLOSE_FD)
		info->to_fd = desc->fd_map.to_fd;
	else if (desc->file_map.to_fd >= 0)
		info->to_fd = desc->file_map.to_fd;
	else
	{
		info->subtype = 12;
		info->dupped2 = dup(STDERR_FILENO);
		if (info->dupped2 == -1)
			return (-1);
		info->to_fd = STDOUT_FILENO;
	}
	info->dupped1 = dup(info->to_fd);
	if (info->dupped1 == -1 && errno != EBADF)
		return (_close_rstore_fds(info), -1);
	new_rd = ft_lstnew(info);
	if (!new_rd)
		return (_close_rstore_fds(info), -1);
	return (ft_lstadd_front(rd_restore, new_rd), 0);
}

int	rd_fd_restore(t_restore_rds *info)
{
	if (!info)
		return (0);
	if (info->subtype == 12)
	{
		if ((info->dupped2 >= 0 && dup2(info->dupped2, STDERR_FILENO) == -1) ||
			((info->dupped2 < 0 && close(STDERR_FILENO) == -1)))
			return (ft_fprintf(2, "minishell: %d: ", STDERR_FILENO));
	}
	if ((info->dupped1 >= 0 && dup2(info->dupped1, info->to_fd) == -1) ||
		((info->dupped1 < 0 && close(info->to_fd) == -1)))
		return (ft_fprintf(2, "minishell: %d: ", info->to_fd));
	_close_rstore_fds(info);
	return (0);
}

void	rd_list_restore(t_list *info_lst)
{
	t_list			*list;

	list = info_lst;
	while (list)
	{
		if (rd_fd_restore(list->content))
			perror(NULL);
		list = list->next;
	}
}
