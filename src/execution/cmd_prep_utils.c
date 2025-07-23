/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:37:48 by cquinter          #+#    #+#             */
/*   Updated: 2025/07/23 13:45:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_path_and_cmd(char ***path, char **dash_cmd, char *cmd, char **envp)
{

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
	char	**path = NULL;
	char	*exec_path;
	char	*dash_cmd = NULL;
	int		i;

	if (set_path_and_cmd(&path, &dash_cmd, cmd, envp))
		perror_exit(shell, "minishell: unable to set cmd");
	i = 0;
	while (path[i])
	{
		exec_path = ft_strjoin(path[i], dash_cmd);
		if (!exec_path)
		{
			free(dash_cmd);
			ft_dirtyswap((void **)&path, NULL, free);
			perror_exit(shell, "minishell: ft_strjoin");
		}
		if (access(exec_path, X_OK) == 0)
			break ;
// this break causes the following free to leak, because break
// means we never free anything after we have found the real path
		free(exec_path); 
		i++;
	}
	if (!path[i])
		return(free(dash_cmd), ft_dirtyswap((void **)&path, NULL, free), NULL);
	return(free(dash_cmd), ft_dirtyswap((void **)&path, NULL, free), exec_path);
}

size_t get_cmd_idx(t_astnode *node)
{
	size_t	i;

	if (!node)
		return (-1);
	i = 0;
	while (i < node->token_count &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != (size_t)-1 &&
		ft_strchr_idx(node->tokens[i][0].raw, '=') != 0)
	{
		if (ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '"') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\'') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '\\') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, ' ') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, ' ') ||
			ft_strchr_idx(node->tokens[i][0].raw, '=') > ft_strchr_idx(node->tokens[i][0].raw, '$') ||
			(node->tokens[i][0].raw[0] != '_' && !ft_isalpha(node->tokens[i][0].raw[0])))
			break;
		i++;
	}
	if (i == node->token_count)
		return (-1);
	return (i);
}

char	**cmdv_prep(t_minishell *shell, t_astnode *node)
{
	char	**argv;
	size_t		i;
	
	argv = ft_calloc(node->token_count + 1, sizeof(char **));
	if (!argv)
		return (NULL);
	i = 0;
	node->cmd_i = get_cmd_idx(node);
	while(i < node->token_count)
	{
		argv[i] = rmv_quotes_xpnd_var(node->tokens[i][0].raw, shell);
		if (!argv)
		{
			ft_dirtyswap((void **)&argv, NULL, free);
			return (NULL);
		}
		i++;
	}
	return (argv);
}
