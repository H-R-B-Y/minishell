/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_local_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:13:15 by hbreeze           #+#    #+#             */
/*   Updated: 2025/06/26 16:54:42 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static ssize_t	local_dir_glob(char ***p)
{
	DIR				*dir;
	char			*cwd;
	struct dirent	*entry;

	if (!p)
		return (-1);
	cwd = getcwd(0, 0);
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	*p = ft_calloc(1, sizeof(char *));
	entry = readdir(dir);
	entry = readdir(dir);
	entry = readdir(dir);
	while (entry)
	{
		ft_dirtyswap((void *)p, ft_arradd_back((void *)*p, ft_strdup(entry->d_name)), free);
		entry = readdir(dir);
	}
	return (ft_arrlen((void *)*p));
}

ssize_t	glob_variable(t_astnode	*node)
{
	ssize_t	i;
	ssize_t	count;
	char	**temp[2];
	char	**output;
	ssize_t	i2;

	i = 0;
	output = ft_calloc(1, sizeof(char *));
	while (node->cmdv[i])
	{
		if (ft_strcmp(node->cmdv[i], "*"))
		{
			ft_dirtyswap((void *)&output, ft_arradd_back((void *)output, node->cmdv[i]), free);
			i++;
			continue;
		}
		count = local_dir_glob(&temp[1]);
		if (count < 0 && ++i)
			continue ;
		i2 = 0;
		while (i2 < count)
			ft_dirtyswap((void *)&output, ft_arradd_back((void *)output, temp[1][i2++]), free);
		i++;
	}
	ft_dirtyswap((void *)&node->cmdv, output, free);
	return (ft_arrlen((void *)node->cmdv));
}
