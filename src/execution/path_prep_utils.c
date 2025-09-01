/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_prep_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:20:32 by cquinter          #+#    #+#             */
/*   Updated: 2025/09/01 12:19:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// NOTE: I think this is actually an older version, I need to push again next time im at 42

int	set_path_and_cmd(char ***path, char **dash_cmd, char *cmd, char **envp)
{
	char	*pathvar;

	*path = NULL;
	*dash_cmd = NULL;
	if (!cmd || !*cmd)
		return (0);
	pathvar = s_get_fromthis_env(envp, "PATH");
	if (!pathvar)
		return (0);
	*path = ft_split(pathvar, ':');
	if (!*path)
		return (1);
	*dash_cmd = ft_strjoin("/", cmd);
	if (!*dash_cmd)
	{
		ft_dirtyswap((void **)path, NULL, free);
		return (1);
	}
	return (0);
}

char	*get_exec_path(t_minishell *shell, char *cmd, char **envp)
{
	char	**path;
	char	*exec_path = 0;
	char	*dash_cmd;
	int		i;

	if (set_path_and_cmd(&path, &dash_cmd, cmd, envp))
		perror_exit(shell, "unable to set cmd");
	i = 0;
	while (path && path[i])
	{
		exec_path = ft_strjoin(path[i], dash_cmd);
		if (!exec_path)
		{
			free(dash_cmd);
			ft_arrclear((void **)path, free);
			perror_exit(shell, "ft_strjoin");
		}
		if (access(exec_path, F_OK) == 0)
			break ;
		free(exec_path);
		i++;
	}
	if (!path || !path[i])
		return (free(dash_cmd), ft_arrclear((void **)path, free), NULL);
	return (free(dash_cmd), ft_arrclear((void **)path, free), exec_path);
}
