/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_prep_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cquinter <cquinter@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 00:20:32 by cquinter          #+#    #+#             */
/*   Updated: 2025/08/14 18:40:32 by cquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_path_and_cmd(char ***path, char **dash_cmd, char *cmd, char **envp)
{
	*path = NULL;
	*dash_cmd = NULL;
	*path = ft_split(s_get_fromthis_env(envp, "PATH"), ':');
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
	char	*exec_path;
	char	*dash_cmd;
	int		i;

	if (set_path_and_cmd(&path, &dash_cmd, cmd, envp))
		perror_exit(shell, "unable to set cmd");
	i = 0;
	while (path[i])
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
	if (!path[i])
		return (free(dash_cmd), ft_arrclear((void **)path, free), NULL);
	return (free(dash_cmd), ft_arrclear((void **)path, free), exec_path);
}
